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

static void			lst_del(t_lst **head, int fd)
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
		return ;
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
			return ;
		}
		temp = curr;
		curr = curr->next;
	}
	printf("DEL ERROR");
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
	while (1)
	{
		if ((ptr->buf)[0] == '\0')
		{
			len = read(fd, ptr->buf, BUFF_SIZE);
			// copy to \n
			if (len < BUFF_SIZE)
			{
				temp = *line;
				*line = ft_strjoin(*line, ptr->buf);
				lst_del(&head, fd);
				if (temp)
					free(temp);
				return (1);
			}
		}
		else
		{
			len = read(fd, ptr->buf, BUFF_SIZE);
		}
	}
	return 1;
}

int			main()
{
	int fd;
	int len;
	char *buf;
	ft_putstr("hiu\n");

	get_next_line(open("test", O_RDONLY), &buf, 0);
	printf("%s\n", buf);

	close(fd);
	return (0);
}