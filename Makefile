
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address,undefined,leak -O0 -g3

SRC = check_map.c parse_colors.c reading_map2.c reading_map.c parse_directions.c parse_directions2.c \
	utils2.c ft_split.c check_pce.c parse_colors2.c cub3d.c utils.c\
	includes/get_next_line.c   includes/get_next_line_utils.c\
	3D_game/ft_malloc.c  3D_game/key_press.c  3D_game/load_texter.c  3D_game/main.c  3D_game/ray_caste.c\
	3D_game/set_player.c

OBJ = $(SRC:.c=.o)
LINK = -lXext -lX11 -lmlx ./minilibx-linux/libmlx.a -lm

NAME = cub3d

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINK) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@printf " \033[1;32m[FILE READY]\033[0m\n"

clean:
	rm -rf $(OBJ)
	@printf " \033[31m[CLEANING DONE]\033[0m\n"

fclean:clean
	rm -rf $(NAME)
	@printf " \033[31m[FULLCLEAN DONE]\033[0m\n"

re : fclean all
.SECONDARY:  $(OBJ)