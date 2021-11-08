/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:59:45 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/08 15:40:04 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	get_line(char **line, char *buffer, size_t last)
{
	char	*tmp;

	if (*line)
	{
		tmp = ft_strnjoin(*line, buffer, last);
		free(*line);
		*line = tmp;
	}
	else
		*line = ft_strnjoin("", buffer, last);
}

int	handle_filled_save(char **line, char **save)
{
	size_t	index;
	char	*tmp;

	index = get_eol(*save);
	if ((*save)[index] == '\n')
	{
		*line = ft_strnjoin("", *save, index + 1);
		if ((*save)[index + 1])
		{
			tmp = ft_strnjoin("", *save + index + 1, BUFFER_SIZE + 1);
			free(*save);
			*save = tmp;
		}
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
	if (last < 0)
		return (0);
	while (last > 0)
	{
		buffer[last] = 0;
		index = get_eol(buffer);
		if (buffer[index] == '\n')
		{
			get_line(line, buffer, index + 1);
			if (buffer[index + 1] != 0)
				*save = ft_strnjoin("", buffer + index + 1, BUFFER_SIZE);
			else if (save)
			{
				free(*save);
				*save = NULL;
			}
			return (1);
		}
		else
			get_line(line, buffer, BUFFER_SIZE + 1);
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
	if (read_file(fd, buffer, &line, &save))
	{
		free(buffer);
		return (line);
	}
	if (save)
	{
		free(save);
		save = NULL;
	}
	free(buffer);
	return (line);
}
