
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address,undefined,leak -O0 -g3

SRC = parsing/check_map.c parsing/parse_colors.c parsing/reading_map2.c parsing/reading_map.c parsing/parse_directions.c parsing/parse_directions2.c \
	parsing/utils2.c parsing/ft_split.c parsing/check_pce.c parsing/parse_colors2.c cub3d.c parsing/utils.c\
	includes/get_next_line.c   includes/get_next_line_utils.c\
	3D_game/ft_malloc.c  3D_game/key_press.c  3D_game/load_texter.c  3D_game/main.c  3D_game/ray_caste.c\
	3D_game/set_player.c 3D_game/mini_map.c 3D_game/mini_map1.c

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