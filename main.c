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

int					read_to_nbr(t_lst *ptr, char **line)
{
	char			*end;
	int				len;
	char			*after;
	char			*before;
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
		*line = ft_strjoin(*line, ft_strncpy(ft_strnew(len), (ptr->buf), len));
		if (del)
			free(del);
//		ft_memcpy(*line, (ptr->buf), len);
		ft_strcpy((ptr->buf), after);
		ft_strclr((ptr->buf) + ft_strlen((ptr->buf)) + 1);
//		printf("COPIED1[%s]\n", *line);
//		printf("LEFT: [%s]\n", (ptr->buf));
		return (1);
	}
	*line = ft_strdup((ptr->buf));
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
	int				res;

//	len = 0;
	ptr = get_node(&head, fd);
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
				if (temp)
					free(temp);
			}
			else
				return (read_to_nbr(ptr, line));
		}
//	printf("LEN: [%d]\n", len);
	if (!(*line) && !(*(ptr->buf)))
//		printf("RETURN0_ADN_DEL\n");
		return (lst_del(&head, fd));
//	printf("RETURN1\n");
	return (1);
}

int			main()
{
	int fd, fd2;
	int len;
	char *buf, *buf2;
	int i = 0;

	fd = open("test", O_RDONLY);
	fd2 = open("test2", O_RDONLY);
	
	while ( i < 10)
	{
		get_next_line(fd2, &buf2);
		get_next_line(fd, &buf);
		printf("PRINTF1:[%s]\n", buf);
		printf("PRINTF2:[%s]\n", buf2);
		if (buf) free(buf);
		if (buf2) free(buf2);
		buf = 0;
		buf2 = 0;
		i++;
	}

	close(fd);
	return (0);
}