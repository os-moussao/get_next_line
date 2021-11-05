

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <bsd/string.h>

#define BUFFER_SIZE 42

size_t	file_append(char **file, size_t len, char *buffer, size_t last)
{
	if (!*file)
	{
		*file = malloc(last + 1);
		strlcat(*file, buffer, last + 1);
		return (last);
	}
	*file = realloc(*file, len + last + 1);
	memmove(file + len, buffer, last);
	file[len + last] = 0;
	return (len + last);
}


char	*get_line(char *file, size_t *off)
{
	size_t	nxt;
	size_t	start;
	size_t	count = 0;
	char	*line;

	nxt = *off;
	start = nxt;
	if (nxt)
		nxt++, start++;
	while (file[nxt] && file[nxt] != 10)
		nxt++;
	line = malloc(nxt - start + 1);
	memmove(line, file + start, nxt - start + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buffer;
	static char		*file;
	static size_t	line_offset;
	size_t			last;
	size_t			len;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);

	buffer = malloc(BUFFER_SIZE + 1);
	buffer[BUFFER_SIZE] = 0;
	while ((last = read(fd, buffer, BUFFER_SIZE)))
		len += file_append(&file, len, buffer, last);
	free(buffer);
	line = get_line(file, &line_offset);
	return (line);
}


int	main(void)
{
	int	fd = open("get_next_line.h", O_RDONLY);
	char	*line;

	while (line = get_next_line(fd))
	{
		printf("%s\n", line);
		free(line);
	}
}
