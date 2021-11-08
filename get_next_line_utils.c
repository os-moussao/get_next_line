/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:56:39 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/08 20:55:46 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_eol(char *buff)
{
	size_t	i;

	i = 0;
	while (buff[i])
		if (buff[i++] == '\n')
			return (i - 1);
	return (i);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	char	*res;
	size_t	len;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len = len1;
	len += (len2 < n) * len2 + (n <= len2) * n;
	res = malloc(len + 1);
	res[len] = 0;
	i = -1;
	while (++i < len && i < len1)
		res[i] = s1[i];
	i--;
	while (++i < len)
		res[i] = s2[i - len1];
	return (res);
}
