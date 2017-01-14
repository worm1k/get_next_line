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
#include <stdio.h>
/*
static void			fl_print_lst(t_lst *lst)
{
	printf("PRINTING:\n");
	while (lst)
	{
		printf("%2d: %s\n", lst->fd, lst->buf);
		lst = lst->next;
	}
}
*/
static int			lst_delone(t_lst **head, int fd)
{
	t_lst			*curr;
	t_lst			*prev;
//	printf("DELETING: %d\n", fd);

	prev = 0;
	curr = *head;
	while (curr)
	{
		if (curr->fd == fd)
		{
			if (prev == 0)
//				printf("DELETED HEAD\n");
				*head = curr->next;
			else
//				printf("DELETED\n");
				prev->next = curr->next;
			free(curr->buf);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
//	printf("DEL ERROR");
	return (0);
}
/*
static int			lst_del(t_lst **head, int fd)
{
	t_lst			*temp;
	t_lst			*curr;
//	printf("DELETING: %d\n", fd);

	if ((*head)->fd == fd)
	{
		temp = (*head)->next;
		free((*head)->buf);
		free(*head);
		*head = temp;
//		printf("DELETED HEAD\n");
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
//			printf("DELETED\n");
			return (0);
		}
		temp = curr;
		curr = curr->next;
	}
//	printf("DEL ERROR");
	return (0);
}
*/
t_lst				*lst_new(int fd)
{
	t_lst			*res;

	res = (t_lst *)malloc(sizeof(t_lst));
	res->next = 0;
	res->fd = fd;
	res->buf = ft_strnew(BUFF_SIZE);
//	if (res->buf)printf("CREATRED\n");
	return (res);
}

t_lst				*get_node(t_lst **head, const int fd, char** line)
{
	t_lst			*temp;
	t_lst			*curr;

	*line = 0;
	curr = *head;
	if (!*head)
	{
//		printf("CREATING FIRST:");
		*head = lst_new(fd);
		curr = *head;
	}
	else
	{
		while (curr)
		{
			if (curr->fd == fd)
			{
//				printf("FOUND RETURN1\n");
				return (curr);
			}
			temp = curr;
			curr = curr->next;
		}
//		printf("ADDING");
		temp->next = lst_new(fd);
//		printf(" RETURN2\n");
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
//		printf("RTNBR_RET0\n");
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
//		ft_memcpy(*line, (ptr->buf), len);
		ft_strcpy((ptr->buf), after);
//		ft_strclr((ptr->buf) + ft_strlen((ptr->buf)) + 1);
//		printf("COPIED1[%s]\n", *line);
//		printf("LEFT: [%s]\n", (ptr->buf));
		return (1);
	}
	*line = ft_strdup((ptr->buf));
	ft_strclr(ptr->buf);
//	printf("COPIED2[%s]\n", *line);
//	printf("LEFT: [%s]\n", (ptr->buf));
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_lst	*head = 0;
	t_lst			*ptr;
	int				len;
	char			*temp;

//	len = 0;
	if (!line || fd < 0)
		return (-1);
	ptr = get_node(&head, fd, line);
	if (!read_to_nbr(ptr, line))
		while((len = read(fd, ptr->buf, BUFF_SIZE)))
		{
			if (len < 0)
				return (-1);
			(ptr->buf)[len] = '\0';
//			printf("READ:[%s]\n", ptr->buf);
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
//	printf("LEN: [%d]\n", len);
	return (!(*line) && !(*(ptr->buf))) ? (lst_delone(&head, fd)) : 1;
//	if (!(*line) && !(*(ptr->buf)))
//		printf("RETURN0_ADN_DEL\n");
//		return (lst_delone(&head, fd));
//	printf("RETURN1\n");
//	return (1);
}
/*

int			main()
{
	int fd;
	int len;
	char *buf;

	fd = open("test", O_RDONLY);
	len = get_next_line(0, &buf);
		printf("%s\n", buf);
	len = get_next_line(0, &buf);
		printf("%s\n", buf);
	len = get_next_line(0, &buf);
		printf("%s\n", buf);

	while ((len = get_next_line(fd, &buf)) > 0)
	{
		printf("%s\n", buf);
		free(buf);
		buf = 0;
	}


	close(fd);
	return (0);
}
*/