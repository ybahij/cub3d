
NAME = cub3d
SRCS = main.c
MLX_DIR = ./minilibx-linux
MLX = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -fsanitize=address -g3

OBJS = $(SRCS:.c=.o)

%.o: %.c
	gcc -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME) $(MLX)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
