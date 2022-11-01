/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:32:42 by kyoulee           #+#    #+#             */
/*   Updated: 2022/10/27 13:31:26 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ft_tool.h>
#include <ft_env_tool.h>

int	ft_echo(int argc, const char *argv[])
{
	int i;
	int	flag;

	i = 1;
	flag = 1;
	ft_setenv("_", argv[0], 1);
	while (i < argc && !ft_strncmp(argv[i], "-n", 2))
	{
		flag = 0;
		i++;
	}
	while (i < argc)
	{
		printf("%s",argv[i++]);
	}
	if (flag)
		printf("\n");
	return (0);
}