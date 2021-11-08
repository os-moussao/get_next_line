/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 21:00:49 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/08 21:00:52 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define FIES_MAX 2000

size_t	ft_strlen(const char *str);
char	*ft_strnjoin(char *s1, char *s2, size_t n);
size_t	get_eol(char *buff);
char	*get_next_line(int fd);

#endif
