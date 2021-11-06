/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:24:55 by omoussao          #+#    #+#             */
/*   Updated: 2021/11/06 17:30:38 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

// how read behaves
int	main(void)
{
	char	buff[22];
	buff[21] = 0;
	int		fd = open("file1", O_RDONLY);
	read(fd, buff, 21);
	printf("%0x\n", buff[20]);
	printf("%s", buff);
}
