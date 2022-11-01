#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <ft_env.h>  
#include <ft_global.h>
#include <ft_tool.h>
#include <ft_cd.h>
#include <ft_pwd.h>
#include <ft_export.h>
#include <ft_unset.h>
#include <ft_exit.h>
#include <ft_echo.h>
#include <ft_dir.h>
#include <ft_file.h>

#include <ft_env_tool.h>
#include <ft_export_tool.h>
#include <ft_terminal.h>

char *ft_stack(char stack[64])
{
	int		rl_len;
	int		stack_len;
	int		i;

	rl_len = ft_strlen(rl_line_buffer);
	i = 0;
	while (i < rl_len)
	{
		stack_len = strlen(stack);
		if (ft_strchr("\'\"", rl_line_buffer[i]))
		{
			if (stack_len && stack[stack_len - 1] == rl_line_buffer[i])
				stack[stack_len - 1] = '\0';
			else
			{
				stack[stack_len + 1] = '\0';
				stack[stack_len] = rl_line_buffer[i];
			}
		}
		i++;
	}
	return (stack);
}


void ft_loop()
{
	char	history_str[2048];
	char	stack[64];

	*stack = '\0';
	while (1)
	{
		*history_str = '\0';
		free(readline("minishell-0.3v : "));
		if (ft_strlen(history_str) + ft_strlen(rl_line_buffer) >= 2048)
			exit(-1);
		ft_strcat(history_str, (const char *)rl_line_buffer);
		ft_strcpy(stack, ft_stack(stack));
		while (*stack)
		{
			free(readline("> "));
			if (ft_strlen(history_str) + ft_strlen(rl_line_buffer) >= 2048)
				exit(-1);
			ft_strcat(history_str, (const char *)rl_line_buffer);
			ft_strcpy(stack, ft_stack(stack));
		}
		ft_cmd_history((const char *)history_str);
		add_history(history_str);
		if (rl_line_buffer[0]=='z')
			break ;
	}
}

int main(void)
{
	struct termios	oldtty;
	struct termios	newtty;
	int 			fd;

	fd = open(ttyname(STDIN_FILENO), O_RDWR | O_NOCTTY );
	if (fd <0)
	{
		perror(ttyname(STDIN_FILENO));
		exit(-1);
	}
	tcgetattr(fd, &oldtty);
	ft_bzero(&newtty, sizeof(struct termios));
	ft_bash_ttyset(&newtty);
	tcsetattr(fd, TCSANOW, &newtty);
	ft_loop();
	tcsetattr(fd, TCSANOW, &oldtty);
}