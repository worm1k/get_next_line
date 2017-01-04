NAME = get_next_line
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB = libft.a
SRC = 	main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)
	
$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

main.o:
	$(CC) -o main.c $(LIB)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf fillit

re: fclean all
	