#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# include <fcntl.h>
# include <unistd.h>
# include "./libft/libft.h"

# define FIES_MAX 2000

char	*get_next_line(int fd);

#endif
