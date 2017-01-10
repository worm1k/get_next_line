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
#include "libft.h"
#include <stdio.h>

static void			fl_print_lst(t_lst *lst)
{
	printf("PRINTING:\n");
	while (lst)
	{
		printf("%2d: %s\n", lst->fd, lst->buf);
		lst = lst->next;
	}
}

static int			lst_del(t_lst **head, int fd)
{
	t_lst			*temp;
	t_lst			*curr;
	printf("DELETING: %d\n", fd);

	if ((*head)->fd == fd)
	{
		temp = (*head)->next;
		free((*head)->buf);
		free(*head);
		*head = temp;
		printf("DELETED HEAD\n");
		return (0);
	}
	temp = *head;
	curr = (*head)->next;
	while (curr)
	{
		if (curr->fd == fd)
		{
			temp->next = curr->next;
			free(curr->buf);
			free(curr);
			printf("DELETED\n");
			return (0);
		}
		temp = curr;
		curr = curr->next;
	}
	printf("DEL ERROR");
	return (1);
}

t_lst				*lst_new(int fd)
{
	t_lst			*res;

	res = (t_lst *)malloc(sizeof(t_lst));
	res->next = 0;
	res->fd = fd;
	res->buf = ft_strnew(BUFF_SIZE);
	if (res->buf)printf("CREATRED\n");
	return (res);
}

t_lst				*get_node(t_lst **head, const int fd)
{
	t_lst			*temp;
	t_lst			*curr;

	curr = *head;
	if (!*head)
	{
		printf("CREATING FIRST:");
		*head = lst_new(fd);
		curr = *head;
	}
	else
	{
		while (curr)
		{
			if (curr->fd == fd)
			{
				printf("FOUND RETURN1\n");
				return (curr);
			}
			temp = curr;
			curr = curr->next;
		}
		printf("ADDING");
		temp->next = lst_new(fd);
		printf(" RETURN2\n");
		return (temp->next);
	}
	return (curr);
}

int					read_to_nbr(char *buf, char **line)
{
	char			*end;

	if (!buf || *buf == '\0')
		return (0);
	end = ft_strchr(buf, '\n');
	if (end)
	{
		*line = ft_strnew(end - buf);
		ft_memcpy(*line, buf, end - buf);
		ft_memmove(buf, buf + (int)(end - buf) + 1, BUFF_SIZE - (int)(end - buf));
		return (1);
	}
	*line = ft_strdup(buf);
	return (1);
}

int					get_next_line(const int fd, char **line, int del)
{
	static t_lst	*head = 0;
	t_lst			*ptr;
	int				len;
	char			*temp;
	int				res;

	ptr = get_node(&head, fd);
	if (del != 0)
	{
		lst_del(&head, del);
		return 0;
	}
	if (!read_to_nbr(ptr->buf, line))
	{
		while((len = read(fd, ptr->buf, BUFF_SIZE)))
			if (!ft_strchr(ptr->buf, '\n'))
			{
				if (len < 0)
					return (-1);
				temp = *line;
				*line = ft_strjoin(*line, ptr->buf);
				if (temp)
					free(temp);
				if (len < BUFF_SIZE)
				{
					lst_del(&head, fd);
					return (1);
				}
			}
			else
				return (read_to_nbr(ptr->buf, line));
		if (!(*line) && len == 0)
			return (0);
	}
	return 1;
}

int			main()
{
	int fd;
	int len;
	char *buf;

	fd = open("test", O_RDONLY);
	
	while (get_next_line(fd, &buf, 0))
	{
		printf("%s\n", buf);
		if (buf) free(buf);
	}

	close(fd);
	return (0);
}