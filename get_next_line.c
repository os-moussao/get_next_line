/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:59:45 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/06 22:15:26 by omoussao         ###   ########.fr       */
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

/*
char	*ft_join_lines(t_list *list)
{

}
*/

char	*get_next_line(int fd)
{
	static char	*save;
	t_list		*line;
	char		*buffer;
	size_t		last;
	size_t		index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	buffer[BUFFER_SIZE] = 0;
	if (save && *save)
	{
		
	}
	else
	{
		index = get_eol(save);
		if (save[index] == '\n')
		{
			// join list
			// return (line)
			tmp = ft_strjoin(line, buffer);
			free(line);
			line = tmp;
			tmp = save + get_eol(save);
			free(save);
			save = tmp;
			return (line);
		}
	}
	while ((last = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[last] = 0;
		index = get_eol(buffer);
		if (!last || get_eol[buffer] == '\n')
		{
			tmp = ft_strjoin(line, buffer);
			free(line);
			line = tmp;
			tmp = save + get_eol(save);
			free(save);
			save = tmp;
			return (line);
		}
		else
		{
			tmp = ft_strjoin(line, buffer);
			free(line);
			line = tmp;
		}
	}
	free(buffer);
	return (line);
}
