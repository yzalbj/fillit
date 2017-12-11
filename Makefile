NAME = fillit

FLAGS = -Wall -Wextra -Werror

SRC = parsing.c main.c data.c resolve.c tools.c

OBJ = $(SRC:.c=.o)

INCLUDE = fillit.h

all: $(NAME)

%.o : %.c $(INCLUDE) 
	gcc $(FLAGS) -c $<

$(NAME): $(OBJ)
	@make -C libft
	gcc -o $(NAME) -I. -L libft -lft $(OBJ)
	@echo "FILLIT COMPILED"
clean:
	@make clean -C libft
	@rm -rf $(OBJ)
	@echo "OBJECTS DELETED"

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "FILLIT DELETED"

re: fclean all

.PHONY: make re clean fclean libft
