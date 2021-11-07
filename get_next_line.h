#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# include <unistd.h>
# include <stdlib.h>

# define FIES_MAX 2000

size_t	ft_strlen(const char *str);
char	*ft_strnjoin(char *s1, char *s2, size_t n);
size_t	get_eol(char *buff);
char	*get_next_line(int fd);

#endif
