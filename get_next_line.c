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

#include "get_next_line.h"

static int			lst_delone(t_lst **head, int fd)
{
	t_lst			*curr;
	t_lst			*prev;

	prev = 0;
	curr = *head;
	while (curr)
	{
		if (curr->fd == fd)
		{
			if (prev == 0)
				*head = curr->next;
			else
				prev->next = curr->next;
			free(curr->buf);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

t_lst				*lst_new(int fd)
{
	t_lst			*res;

	res = (t_lst *)malloc(sizeof(t_lst));
	res->next = 0;
	res->fd = fd;
	res->buf = ft_strnew(BUFF_SIZE);
	return (res);
}

t_lst				*get_node(t_lst **head, const int fd, char **line)
{
	t_lst			*temp;
	t_lst			*curr;

	*line = 0;
	curr = *head;
	if (!*head)
	{
		*head = lst_new(fd);
		curr = *head;
	}
	else
	{
		while (curr)
		{
			if (curr->fd == fd)
			{
				return (curr);
			}
			temp = curr;
			curr = curr->next;
		}
		temp->next = lst_new(fd);
		return (temp->next);
	}
	return (curr);
}

int					read_to_nbr(t_lst *ptr, char **line)
{
	char			*end;
	int				len;
	char			*after;
	char			*del;

	if (!(ptr->buf) || *(ptr->buf) == '\0')
		return (0);
	end = ft_strchr((ptr->buf), '\n');
	len = end - (ptr->buf);
	after = (ptr->buf) + len + 1;
	del = 0;
	if (end)
	{
		del = *line;
		end = ft_strnew(len);
		*line = ft_strjoin(*line, ft_strncpy(end, (ptr->buf), len));
		free(end);
		if (del)
			free(del);
		ft_strcpy((ptr->buf), after);
		return (1);
	}
	*line = ft_strdup((ptr->buf));
	ft_strclr(ptr->buf);
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_lst	*head = 0;
	t_lst			*ptr;
	int				len;
	char			*temp;

	if (!line || fd < 0)
		return (-1);
	ptr = get_node(&head, fd, line);
	if (!read_to_nbr(ptr, line))
		while ((len = read(fd, ptr->buf, BUFF_SIZE)))
		{
			if (len < 0)
				return (-1);
			(ptr->buf)[len] = '\0';
			if (!ft_strchr(ptr->buf, '\n'))
			{
				temp = *line;
				*line = ft_strjoin(*line, ptr->buf);
				(temp) ? free(temp) : 0;
				ft_strclr(ptr->buf);
			}
			else
				return (read_to_nbr(ptr, line));
		}
	return (!(*line) && !(*(ptr->buf))) ? (lst_delone(&head, fd)) : 1;
}
