/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:59:45 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/07 16:15:07 by omoussao         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*buffer;
	char		*tmp;
	ssize_t		last;
	size_t		index;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	buffer[BUFFER_SIZE] = 0;

	// don't check first char untill its not null
	if (save && *save)
	{
		index = get_eol(save);
		if (save[index] == '\n')
		{
			line = ft_strnjoin("", save, index + 1);
			
			// update save
			tmp = ft_strnjoin("", save + index + 1, BUFFER_SIZE + 1);
			free(save);
			save = tmp;

			free(buffer);
			return (line);
		}
		else
		{
			// line = ft_strnjoin("", save, BUFFER_SIZE + 1); // like strdup
			// free(save); // could be done inside strnjoin (pba)
			// save = NULL;
			line = save;
			save = NULL;
		}
	}
	// else if save is empthy or is does not hold a newline
	last = read(fd, buffer, BUFFER_SIZE);
	if (last < 0)
	{
		free(buffer);
		return (NULL);
	}
	while (last > 0)
	{
		buffer[last] = 0;
		index = get_eol(buffer);
		if (buffer[index] == '\n')
		{
			get_line(&line, buffer, index + 1);

			save = ft_strnjoin("", buffer + index + 1, BUFFER_SIZE);

			free(buffer);
			return (line);
		}
		else
			get_line(&line, buffer, BUFFER_SIZE + 1);
		last = read(fd, buffer, BUFFER_SIZE);
	}
	if (save)
		free(save);
	free(buffer);
	return (line);
}
