/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:32:37 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/05 10:52:43 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

static char	*get_line(int fd, size_t offset)
{
	char	buffer[1000] = {0};
	char	*line;
	size_t	i;
	size_t	lines = 0;
	char	c = 0;

	while (lines < offset)
	{
		while (c != 10)
			read(fd, &c, 1);
		lines++;
		c = 0;
	}

	i = 0;
	while (read(fd, &buffer[i], 1))
	{
		if (buffer[i++] == 10 || !buffer[i])
			break ;
	}

	if (i == 0)
		return (NULL);

	line = calloc(i + 1, 1);
	if (!line)
		return (NULL);
	strlcpy(line, buffer, i + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static size_t	offset;
	char			*line;

	offset = 0;
	line = get_line(fd, offset++);
	return (line);
}

int	main(void)
{
	char	*line;
	int		fd = open("file.txt", O_RDONLY);
	if (fd  == -1)
	{
		printf("open error\n");
		return (1);
	}

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
}
