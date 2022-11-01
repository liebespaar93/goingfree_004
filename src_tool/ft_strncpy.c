/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:34:59 by kyoulee           #+#    #+#             */
/*   Updated: 2022/10/24 20:04:39 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
char	*ft_strncpy(char *str, size_t len)
{
	char	*tmp;
	char	*result;

	if (len == 0)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) *(len + 1));
	if (!tmp)
		return (NULL);
	result = tmp;
	tmp[len] = '\0';
	while (len--)
		*tmp++ = *str++;
	return (result);
}