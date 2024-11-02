
NAME = cub3d
SRCS = main.c
MLX_DIR = ./minilibx-linux
MLX = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz -fsanitize=address

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