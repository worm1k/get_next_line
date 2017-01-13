NAME = get_next_line
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB = libft.a
SRC = get_next_line.c
OBJ = get_next_line.o

all: $(NAME)
	
$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

$(OBJ): $(SRC)
	$(CC) -c $(SRC)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
	