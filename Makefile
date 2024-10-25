NAME = cub3d
SRC = main.c
OBJ = $(SRC:.c=.o)
MLX_LIB = libmlx.a -framework OpenGL -framework AppKit -fsanitize=address -g3

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) $(MLX_LIB) -o $(NAME)

%.o: %.c
	cc -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re