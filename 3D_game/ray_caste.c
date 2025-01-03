#include "../cub3d.h"

void	ray_dist(t_player *player)
{
	if (player->ray_dir_x < 0)
	{
		player->step_x = -1;
		player->side_dist_x = (player->px - player->map_x) * player->delta_dist_x;
	}
	else
	{
		player->step_x = 1;
		player->side_dist_x = (player->map_x + 1.0 - player->px) * player->delta_dist_x;
	}
	if (player->ray_dir_y < 0)
	{
		player->step_y = -1;
		player->side_dist_y = (player->py - player->map_y) * player->delta_dist_y;
	}
	else
	{
		player->step_y = 1;
		player->side_dist_y = (player->map_y + 1.0 - player->py) * player->delta_dist_y;
	}
}

void	ray_dir(double  angle_increment,t_player *player)
{
	player->ray_angle = player->angle - (FOV / 2) + player->x * angle_increment;
	player->ray_dir_x = cos(player->ray_angle);
	player->ray_dir_y = sin(player->ray_angle);
	player->map_x = (int)player->px;
	player->map_y = (int)player->py;
	player->delta_dist_x = fabs(1 / player->ray_dir_x);
	player->delta_dist_y = fabs(1 / player->ray_dir_y);
	ray_dist(player);
}

void	ray_travel(t_player *player)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (player->side_dist_x < player->side_dist_y)
		{
			player->side_dist_x += player->delta_dist_x;
			player->map_x += player->step_x;
			player->side = 0;
		}
		else
		{
			player->side_dist_y += player->delta_dist_y;
			player->map_y += player->step_y;
			player->side = 1;
		}
		if (player->map[player->map_y][player->map_x] == '1')
			hit = 1;
	}
}

void	wall_height(t_player *player)
{
	if (player->side == 0)
		player->perp_wall_dist = (player->map_x - player->px + (1 - player->step_x) / 2)
			/ player->ray_dir_x;
	else
		player->perp_wall_dist = (player->map_y - player->py + (1 - player->step_y) / 2)
			/ player->ray_dir_y;
	player->perp_wall_dist *= cos(player->angle - player->ray_angle);
	player->line_height = (int)(WINDOW_HEIGHT / player->perp_wall_dist);
	player->draw_start = WINDOW_HEIGHT / 2 - player->line_height / 2;
	if (player->draw_start < 0)
		player->draw_start = 0;
	player->draw_end = player->line_height / 2 + WINDOW_HEIGHT / 2;
	if (player->draw_end >= WINDOW_HEIGHT)
		player->draw_end = WINDOW_HEIGHT - 1;
}

void	ceiling_floor_color(t_player *player)
{
	player->y = 0;
	while (player->y < player->draw_start)
	{
		player->screen_player[player->y * WINDOW_WIDTH + player->x] = player->ceiling_color;
		player->y++;
	}
	player->y = player->draw_end;
	while (player->y < WINDOW_HEIGHT)
	{
		player->screen_player[player->y * WINDOW_WIDTH + player->x] = player->floor_color;
		player->y++;
	}
}