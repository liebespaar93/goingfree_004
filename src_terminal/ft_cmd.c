#include <stdio.h>
#include <stdlib.h>
#include <ft_tool.h>
#include <ft_env_tool.h>
#include <ft_export_tool.h>
#include <ft_terminal.h>
#include <sys/syslimits.h>

char	*ft_trans_env(char **str)
{
	char	*temp;
	char	*env_str;
	
	(*str)++;
	temp = *str;
	while (*temp && ft_isenv(*temp))
		temp++;
	if (temp == *str)
		return ("$");
	env_str = ft_strncpy(*str, temp - *str);
	*str = temp;
	temp = getenv(env_str);
	free(env_str);
	return (temp);
}

char *ft_inhibit(const char *history)
{
	char	str[ARG_MAX];
	char	stack;

	ft_bzero(str, sizeof(char [ARG_MAX]));
	stack = '\0';
	while (*history)
	{
		if (ft_strchr("\'\"", *history))
		{
			if (!stack)
				stack = *history;
			else if (stack == *history)
				stack = '\0';
			else
				str[ft_strlen(str)] = *history;
			history++;
		}
		else if ((!stack || stack == '\"') && *history == '$')
			ft_strcat(str, ft_trans_env((char **)&history));
		else
			str[ft_strlen(str)] = *history++;
	}
	return (ft_strdup(str));
}




void ft_cmd(const char *history)
{
	char *str;
	
	str = ft_inhibit(history);

	printf("\033[38;5;160m history : '%s'\n", history);
	printf("\033[38;5;021m ft_inhibit : '%s'\n\033[0m", str);

}

int	ft_cmd_argc(char *history_str)
{
	int	argc;
	int	i;
	int flag;
	
	i = 0;
	argc = 0;
	flag = 0;
	while (history_str[i])
	{
		if (ft_strchr(WHITE_SPACE, history_str[i]))
		{
			if (flag)
				argc++;
			flag = 0;
		}
		else if (history_str[i] == '\'')
		{
			i++;
			while (history_str[i] && history_str[i] != '\'')
				i++;
			flag = 1;
		}
		else if (history_str[i] == '\"')
		{
			i++;
			while (history_str[i] && history_str[i] != '\"')
				i++;
			flag = 1;
		}
		else
			flag = 1;
		i++;
	}
	if (flag)
		argc++;
	return (argc);
}

char	**ft_cmd_argv(t_cmd *cmd, char *history_str)
{
	int	i;
	int	size;
	int	index;

	if (cmd->argc == 0)
		return (NULL);
	cmd->argv = (char **)malloc(sizeof(char *) * (cmd->argc));
	if (!cmd->argv)
		return (NULL);
	i = 0;
	size = 0;
	index = 0;
	while (history_str[i])
	{
		if (ft_strchr(WHITE_SPACE, history_str[i]))
		{
			if (size)
			{
				printf("size : %d %c \n", size, history_str[i -1]);
				cmd->argv[index++] = ft_strncpy(history_str + i - 1 - size, size + 1);
				size = 0;
			}
			i++;
		}
		else if (history_str[i] == '\'')
		{
			i++;
			while (history_str[i++] != '\'')
				size++;
			size++;
		}
		else if (history_str[i] == '\"')
		{
			i++;
			while (history_str[i++] != '\"')
				size++;
			size++;
		}
		else
		{
			i++;
			size++;
		}
	}
	if (size)
	{
		printf("size : %d %c \n", size, history_str[i -1]);
		cmd->argv[index++] = ft_strncpy(history_str + i - size, size);
		size = 0;
	}
	return (cmd->argv);
}

int	ft_cmd_init(t_cmd *cmd, char *history_str)
{
	if (!cmd)
		return (0);
	cmd->argc = ft_cmd_argc(history_str);
	printf(" cmd->argc : %d\n", cmd->argc);
	if (!cmd->argc)
		return (0);
	if (!ft_cmd_argv(cmd, history_str))
		return (0);
	int i;

	i = 0;
	printf(" cmd->argv :");
	while (i < cmd->argc)
	{
		printf("[%d]%s  ",i,cmd->argv[i]);
		i++;
	}
	printf("\n");
	return (1);
}