#include <stdio.h>
#include <stdlib.h>
#include <ft_tool.h>
#include <ft_env_tool.h>
#include <ft_export_tool.h>


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
	char	str[100000];
	char	stack;

	ft_bzero(str, sizeof(char [100000]));
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