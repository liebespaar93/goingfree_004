/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tty_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:55:35 by kyoulee           #+#    #+#             */
/*   Updated: 2022/11/07 08:34:21 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <readline/readline.h>
#include <readline/history.h>
#include <ft_tool.h>
#include <stdlib.h>
#include <ft_terminal.h>
#include <sys/syslimits.h>

int ft_work(char *history_str)
{
	int		history_start;
	int		history_end;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	history_start = 0;
	history_end = 0;
	while (rl_line_buffer[i])
	{
		if (!ft_strncmp("\"", rl_line_buffer + i , 1) && ++flag)
		{
			i++;
			while (ft_strncmp("\"", rl_line_buffer + i , 1))
			{
				if (!rl_line_buffer[++i])
				{
					printf("in > \" \n");
					free(readline("> "));
					ft_strcat(history_str, rl_line_buffer);
					history_end += i;
					i = 0;
				}
			}
			i++;
		}
		else if (!ft_strncmp("\'", rl_line_buffer + i, 1) && ++flag)
		{
			i++;
			while (ft_strncmp("\'", rl_line_buffer + i, 1))
			{
				if (!rl_line_buffer[++i])
				{
					printf("in > \' \n");
					free(readline("> "));
					ft_strcat(history_str, rl_line_buffer);
					history_end += i;
					i = 0;
				}
			}
			i++;
		}
		else if (!ft_strncmp("||", rl_line_buffer + i, 2))
		{
			i += 2;
			if (!flag && printf("syntax error near unexpected token `||'\n"))
				return(ERROR_SYNTAX);
			while (!rl_line_buffer[i] || ft_strchr(WHITE_SPACE, rl_line_buffer[i]))
			{
				if (!rl_line_buffer[i])
				{
					printf("in > || \n");
					if (history_str[ft_strlen(history_str) - 1] == '\n')
						history_str[ft_strlen(history_str) - 1] = ' ';
					free(readline("> "));
					ft_strcat(history_str, rl_line_buffer);
					history_end += i;
					i = 0;
				}
				else
					i++;
			}
			flag = 0;
		}
		else if (!ft_strncmp("&&", rl_line_buffer + i, 2))
		{
			i += 2;
			if (!flag && printf("syntax error near unexpected token `&&'\n"))
				return(ERROR_SYNTAX);
			while (!rl_line_buffer[i] || ft_strchr(WHITE_SPACE, rl_line_buffer[i]))
			{
				if (!rl_line_buffer[i])
				{
					printf("in > && \n");
					if (history_str[ft_strlen(history_str) - 1] == '\n')
						history_str[ft_strlen(history_str) - 1] = ' ';
					free(readline("> "));
					ft_strcat(history_str, rl_line_buffer);
					history_end += i;
					i = 0;
				}
				else
					i++;
			}
			flag = 0;
		}
		else if (!ft_strncmp("|", rl_line_buffer + i, 1))
		{
			i++;
			if (!flag && printf("syntax error near unexpected token `|'\n"))
				return(ERROR_SYNTAX);
			//ft_pipe_child(history_str, history_start, history_end, i);
			/*
				fork 실행 ( 자식 실행) 
			*/
			history_start = history_end + i;
			while (!rl_line_buffer[i] || ft_strchr(WHITE_SPACE, rl_line_buffer[i]))
			{
				if (!rl_line_buffer[i])
				{
					printf("in > | \n");
					if (history_str[ft_strlen(history_str) - 1] == '\n')
						history_str[ft_strlen(history_str) - 1] = ' ';
					free(readline("> "));
					ft_strcat(history_str, rl_line_buffer);
					history_end += i;
					i = 0;
				}
				else
					i++;
			}
			flag = 0;
		}
		else
		{
			if (!ft_strchr(WHITE_SPACE, rl_line_buffer[i]))
				flag = 1;
			i++;
		}
	}
	return (history_start);
}


#include <ft_file.h>

void ft_exe(char *history_str)
{
	t_cmd	cmd;
	
	if (!ft_cmd_init(&cmd, history_str))
		return ;
	if (ft_strncmp(cmd.argv[0], "echo", 4))
	{

	}
	else if (ft_strncmp(cmd.argv[0], "cd", 2))
	{
		
	}
	else if (ft_strncmp(cmd.argv[0], "export", 6))
	{
		
	}
	else if (ft_strncmp(cmd.argv[0], "unset", 5))
	{
		
	}
	else if (ft_strncmp(cmd.argv[0], "env", 3))
	{
		
	}
	else if (ft_strncmp(cmd.argv[0], "exit", 3))
	{
		
	}
	else if (ft_strncmp(cmd.argv[0], ".", 1))
	{
		
	}
	else
	{
		//ft_get_file(cmd.argv[0]);
	}

}

void ft_tty_loop()
{
	char	history_str[ARG_MAX];
	int		last_cmd;
	
	ft_bzero(history_str, sizeof(char [ARG_MAX]));
	while (1)
	{
		*history_str = '\0';
		free(readline("\033[38;5;226mminishell-0.3v : \033[0m"));
		ft_strcat(history_str, rl_line_buffer);
		last_cmd = ft_work(history_str);
		if (last_cmd)
		{
			/* fork 할것! (자식 실행)*/
		}
		else
		{
			/*집접 실행 (부모실행)*/
			ft_exe(history_str + last_cmd);
		}
		add_history(history_str);
		printf("history : %s\n",history_str);
	}
}