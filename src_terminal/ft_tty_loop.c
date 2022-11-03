/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tty_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:55:35 by kyoulee           #+#    #+#             */
/*   Updated: 2022/11/03 18:04:32 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <readline/readline.h>
#include <readline/history.h>
#include <ft_tool.h>
#include <stdlib.h>
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
		stack_len = ft_strlen(stack);
		if (ft_strchr("\'\"&|", rl_line_buffer[i]))
		{
			if (stack_len && stack[stack_len - 1] == rl_line_buffer[i])
				stack[stack_len - 1] = '\0';
			else if (!stack_len || !ft_strchr("\'\"", stack[stack_len - 1]))
				stack[stack_len] = rl_line_buffer[i];
		}
		i++;
	}
	return (stack);
}

void ft_tty_loop()
{
	char	history_str[2048];
	char	stack[64];

	ft_bzero(stack, sizeof(char [64]));
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
		ft_cmd((const char *)history_str);
		add_history(history_str);
		if (rl_line_buffer[0]=='z')
			break ;
	}
}