NAME = get_next_line
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB = libft.a
SRC = 	main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)
	
$(NAME): $(OBJ)
	$(CC) -o a $(OBJ) $(LIB)

main.o:
	$(CC) -c main.c

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf a

re: fclean all
	