#include "../cub3d.h"

void	set_angle(t_player *player)
{
	player->mlx = NULL;
	player->mlx_win = NULL;
	if (player->start_angle == 'N')
		player->angle = 0;
	else if (player->start_angle == 'E')
		player->angle = PI / 2;
	else if (player->start_angle == 'S')
		player->angle = PI;
	else if (player->start_angle == 'W')
		player->angle = 3 * PI / 2;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);

}

int rgb_to_int(int *color, int r, int g, int b)
{
	(void)color;
	return (r << 16 | g << 8 | b);
}

void get_player_position(t_player *player)
{
	int i, j;

	i = 0;
	player->ceiling_color = rgb_to_int(NULL, player->color_c[0],  player->color_c[1], player->color_c[2]);
	player->floor_color = rgb_to_int(NULL, player->color_f[0], player->color_f[1], player->color_f[2]);
	while (player->map[i])
	{
		j = 0;
		while (player->map[i][j])
		{
			if (player->map[i][j] == 'W' || player->map[i][j] == 'N'
				|| player->map[i][j] == 'E' || player->map[i][j] == 'S')
			{
				player->start_angle = player->map[i][j];
				player->px = j + 0.5;
				player->py = i + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

