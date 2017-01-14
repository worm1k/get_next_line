/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 18:15:41 by abykov            #+#    #+#             */
/*   Updated: 2017/01/03 18:15:42 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include "libft/libft.h"
# define GET_NEXT_LINE_H
# define BUFF_SIZE 2

int					get_next_line(const int fd, char **line);
typedef struct		s_lst
{
	struct s_lst	*next;
	char			*buf;
	int				fd;
}					t_lst;

#endif
