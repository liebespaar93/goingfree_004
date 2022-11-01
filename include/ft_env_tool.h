/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_tool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:27:06 by kyoulee           #+#    #+#             */
/*   Updated: 2022/10/24 14:14:55 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_TOOL_H
# define FT_ENV_TOOL_H

int ft_envargs(void);
int	ft_unsetenv(const char *name);
int	ft_putenv(const char *str);
int	ft_setenv(const char *name, const char *value, int overwrite);

char **ft_environ_addr(char **name_ptr);

#endif