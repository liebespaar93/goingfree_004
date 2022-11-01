/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tool.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:19:40 by kyoulee           #+#    #+#             */
/*   Updated: 2022/11/01 16:49:33 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOOL_H
# define FT_TOOL_H

#include <sys/_types/_size_t.h>

size_t	ft_void_len(void *ptr[]);
size_t	ft_strlen(const char *str);
size_t	ft_strcpy(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *str, size_t len);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);

char	*ft_strjoin(const char *s1, const char *s2);


void	ft_bzero(void *s, size_t n);

int		ft_isalpha(int c);
int		ft_isdigit(int c);


int		ft_atoi(const char *str);
char	*ft_itoa(int n);

#endif