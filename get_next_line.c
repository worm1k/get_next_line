#include "get_next_line.h"
#include "libft.h"

void ft_read(int fd)
{
	char buf[2];

	read(fd, buf, 1);
	printf("READ:%c\n", buf[0]);
}

int		get_next_line(const int fd, char **line)
{
	char	buf[BUFF_SIZE];
	int		i;
	int		check;
	char	*temp;
	int		res;

	i = 0;
	res = -1;
	ft_bzero(buf, BUFF_SIZE);
	while(check = read(fd, buf + i, 1))
	{
		printf("READ:%c\n", *(buf + i));
		if (check == EOF)
		{
			temp = *line;
			*line = ft_strjoin(*line, buf);
			if (temp) free(temp);
			res = 0;
			break ;
		}
		if (buf[i] == '\n')
		{
			printf("NBR\n");
			temp = *line;
			printf("111\n");
			*line = ft_strjoin(*line, buf);
			printf("222\n");
			if (temp) free(temp);
			printf("333\n");
			res = 1;
			printf("444\n");
			break ;
		}
		i++;
		if (i == BUFF_SIZE - 1)
		{
			temp = *line;
			*line = ft_strjoin(*line, buf);
			if (temp) free(temp);
			i = 0;
			continue ;
		}
	}

	printf("655\n");
	return (res);
}

int main()
{
	int fd;
	char *res;

	fd = open("test.txt", O_RDONLY);/*
	ft_read(fd);
	ft_read(fd);
	ft_read(fd);
	ft_read(fd);*/
	
	int val = get_next_line(fd, &res);
	printf("NEXTLINE: %s\nRES: %d", res, val);
	free(res);
	res = 0;
	val = get_next_line(fd, &res);
	printf("NEXTLINE: %s\nRES: %d", res, val);
	free(res);
	res = 0;
	val = get_next_line(fd, &res);
	printf("NEXTLINE: %s\nRES: %d", res, val);
	return (0);
}