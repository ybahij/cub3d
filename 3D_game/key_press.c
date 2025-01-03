#include"../cub3d.h"

void	rotate_player(t_player *player, float angle)
{
	float	old_dir_x;

	player->angle += angle;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	draw_3d_view(player);
}

void	destroy_img(t_texture *texture, t_player *player)
{
	if (texture)
	{
		if (texture->img)
			mlx_destroy_image(player->mlx, texture->img);
	}
}

int	close_window(void *params)
{
	t_player	*player;

	player = (t_player *)params;

	if (player->mlx_win)
		mlx_destroy_window(player->mlx, player->mlx_win);
	if (player->north_texture)
		destroy_img(player->north_texture, player);
	if (player->south_texture)
		destroy_img(player->south_texture, player);
	if (player->west_texture)
		destroy_img(player->west_texture, player);
	if (player->east_texture)
		destroy_img(player->east_texture, player);
	if (player->screen_img)
		mlx_destroy_image(player->mlx, player->screen_img);
	if (player->mlx)
		mlx_destroy_display(player->mlx);
	garbage_collector();
	exit(0);
}


int	key_press(int keycode, void *params)
{
	t_player	*player;

	player = (t_player *)params;
	if (keycode == 65307)
		close_window(player);
	else if (keycode == 119 || keycode == 65362)
		move_player(player, player->dir_x * MOVE_SPEED, player->dir_y
			* MOVE_SPEED);
	else if (keycode == 115 || keycode == 65364)
		move_player(player, -player->dir_x * MOVE_SPEED, -player->dir_y
			* MOVE_SPEED);
	else if (keycode == 100)
		move_player(player, -player->dir_y * MOVE_SPEED, player->dir_x
			* MOVE_SPEED);
	else if (keycode == 97)
		move_player(player, player->dir_y * MOVE_SPEED, -player->dir_x
			* MOVE_SPEED);
	else if (keycode == 65361)
		rotate_player(player, -ROTATE_SPEED);
	else if (keycode == 65363)
		rotate_player(player, ROTATE_SPEED);
	return (0);
}

void	move_player(t_player *player, float dx, float dy)
{
	float new_px, new_py;
	new_px = player->px + dx;
	new_py = player->py + dy;
	if (player->map[(int)new_py][(int)new_px] != '1')
	{
		if (player->map[(int)new_py][(int)player->px] != '1'
			|| player->map[(int)player->py][(int)new_px] != '1')
		{
			player->px = new_px;
			player->py = new_py;
			draw_3d_view(player);
		}
	}
	else
	{
		if (player->map[(int)player->py][(int)new_px] != '1')
		{
			player->px = new_px;
			draw_3d_view(player);
		}
		else if (player->map[(int)new_py][(int)player->px] != '1')
		{
			player->py = new_py;
			draw_3d_view(player);
		}
	}
	return ;
}