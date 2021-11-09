/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:59:45 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/09 21:01:58 by omoussao         ###   ########.fr       */
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

void	ft_strnjoin(char **to_fill, char *s1, char *s2, size_t n)
{
	char	*res;
	size_t	len;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!*to_fill)
		s1 = "";
	len1 = 0;
	while (s1[len1])
		len1++;
	len2 = 0;
	while (s2[len2])
		len2++;
	res = malloc((len = len1 + (len2 < n) * len2 + (n <= len2) * n) + 1);
	res[len] = 0;
	i = -1;
	while (++i < len1)
		res[i] = s1[i];
	i--;
	while (++i < len)
		res[i] = s2[i - len1];
	if (*to_fill)
		free(*to_fill);
	*to_fill = res;
}

int	handle_filled_save(char **line, char **save)
{
	size_t	index;

	index = get_eol(*save);
	if ((*save)[index] == '\n')
	{
		ft_strnjoin(line, "", *save, index + 1);
		if ((*save)[index + 1])
			ft_strnjoin(save, "", *save + index + 1, BUFFER_SIZE + 1);
		else
		{
			free(*save);
			*save = NULL;
		}
		return (1);
	}
	*line = *save;
	*save = NULL;
	return (0);
}

int	read_file(int fd, char *buffer, char **line, char **save)
{
	size_t	index;
	ssize_t	last;

	last = read(fd, buffer, BUFFER_SIZE);
	while (last > 0)
	{
		buffer[last] = 0;
		index = get_eol(buffer);
		if (buffer[index] == '\n')
		{
			ft_strnjoin(line, *line, buffer, index + 1);
			if (buffer[index + 1] != 0)
				ft_strnjoin(save, "", buffer + index + 1, BUFFER_SIZE);
			else if (save)
			{
				free(*save);
				*save = NULL;
			}
			return (1);
		}
		else
			ft_strnjoin(line, *line, buffer, BUFFER_SIZE + 1);
		last = read(fd, buffer, BUFFER_SIZE);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*buffer;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save && *save)
		if (handle_filled_save(&line, &save))
			return (line);
	buffer = malloc(BUFFER_SIZE + 1);
	buffer[BUFFER_SIZE] = 0;
	read_file(fd, buffer, &line, &save);
	free(buffer);
	return (line);
}
