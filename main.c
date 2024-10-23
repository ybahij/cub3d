// #include "minilibx-linux/mlx.h"
// #include <math.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MOVE_SPEED 0.2
// #define ROTATE_SPEED 0.15

// typedef struct s_player
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	void	*mlx_bg;
// 	float	px;
// 	float	py;
// 	float	dir_x;
// 	float	dir_y;
// 	char	**map;
// }			t_player;

// void draw_line(void *mlx, void *mlx_win, int x0, int y0, int x1, int y1, int color, char **map)
// {
//     float dx;
//     float dy;
//     float steps;
//     float x_inc;
//     float y_inc;
//     float x;
//     float y;

//     dx = x1 - x0;
//     dy = y1 - y0;
//     x = x0;
//     y = y0;
//     if (fabs(dx) > fabs(dy))
//         steps = fabs(dx);
//     else
//         steps = fabs(dy);
//     x_inc = dx / steps;
//     y_inc = dy / steps;

//     while (steps-- >= 0)
//     {
//         if (map[(int)(y / 100)][(int)(x / 100)] == '1')
//             break;
//         mlx_pixel_put(mlx, mlx_win, (int)x, (int)y, color);
//         x += x_inc;
//         y += y_inc;
//     }
// }


// void draw_view_cone(void *mlx, void *mlx_win, int center_x, int center_y, double dir_x, double dir_y, double fov, int length, int color, char **map)
// {
//     double half_fov = fov / 2.0;
//     double start_angle = atan2(dir_y, dir_x) - half_fov;
//     double end_angle = atan2(dir_y, dir_x) + half_fov;
//     int num_lines = 50;
//     double angle_increment = (end_angle - start_angle) / num_lines;

//     int i = 0;
//     while (i <= num_lines)
//     {
//         double angle = start_angle + i * angle_increment;
//         int end_x = center_x + (int)(cos(angle) * length);
//         int end_y = center_y + (int)(sin(angle) * length);
//         draw_line(mlx, mlx_win, center_x, center_y, end_x, end_y, color, map);
//         i++;
//     }
// }

// void	draw_player(t_player *player)
// {
// 	int	radius;
// 	int	center_x;
// 	int	center_y;
// 	int	line_x;
// 	int	line_y;

// 	radius = 5;
// 	center_x = (int)(player->px * 100);
// 	center_y = (int)(player->py * 100);
//     int x, y;
//     y = -radius;
//     while (y <= radius)
//     {
//         x = -radius;
//         while (x <= radius)
//         {
//             if (x * x + y * y <= radius * radius)
//             {
//                 mlx_pixel_put(player->mlx, player->mlx_win, center_x + x,
//                     center_y + y, 0x00FFFFFF);
//             }
//             x++;
//         }
//         y++;
//     }
// 	line_x = center_x;
// 	line_y = center_y;
// 	while (player->map[line_y / 100][line_x / 100] != '1')
// 	{
// 		line_x += (int)(player->dir_x * 12);
// 		line_y += (int)(player->dir_y * 12);
// 	}
//     draw_view_cone(player->mlx, player->mlx_win, center_x, center_y, player->dir_x, player->dir_y, M_PI / 3, 1000, 0x00FFFFFF, player->map);
// }

// void	draw_map1(t_player *player)
// {
// 	int	size;
// 	int	i;
// 	int	j;
// 	int	k;

// 	size = 100;
// 	i = 0;
// 	while (player->map[i])
// 	{
// 		j = 0;
// 		while (player->map[i][j])
// 		{
// 			mlx_put_image_to_window(player->mlx, player->mlx_win,
// 				player->mlx_bg, j * size, i * size);
// 			if (player->map[i][j] == '1')
// 			{
// 				k = 0;
// 				while (k < size)
// 				{
//                     mlx_pixel_put(player->mlx, player->mlx_win, j * size + k, i
//                         * size, 0x0000FF00);
//                     mlx_pixel_put(player->mlx, player->mlx_win, j * size + k, i
//                         * size + size - 1, 0x00FF00FF);
//                     mlx_pixel_put(player->mlx, player->mlx_win, j * size, i
//                         * size + k, 0x000000FF);
//                     mlx_pixel_put(player->mlx, player->mlx_win, j * size + size
//                         - 1, i * size + k, 0x00FFFF00);
// 					k++;
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	draw_player(player);
// }


// void	draw_map(t_player *player)
// {
// 	int	size;
// 	int	i;
// 	int	j;

// 	size = 100;
// 	i = 0;
// 	while (player->map[i])
// 	{
// 		j = 0;
// 		while (player->map[i][j])
// 		{
//             if (player->map[i][j] != '1')
// 				mlx_put_image_to_window(player->mlx, player->mlx_win,
// 					player->mlx_bg, j * size, i * size);
// 			j++;
// 		}
// 		i++;
// 	}
// 	draw_player(player);
// }

// void	move_forward(t_player *player)
// {
// 	float	new_px;
// 	float	new_py;

// 	new_px = player->px + player->dir_x * MOVE_SPEED;
// 	new_py = player->py + player->dir_y * MOVE_SPEED;
// 	if (player->map[(int)new_py][(int)new_px] != '1')
// 	{
// 		player->px = new_px;
// 		player->py = new_py;
// 	}
// 	draw_map(player);
// }

// void	move_backward(t_player *player)
// {
// 	float	new_px;
// 	float	new_py;

// 	new_px = player->px - player->dir_x * MOVE_SPEED;
// 	new_py = player->py - player->dir_y * MOVE_SPEED;
// 	if (player->map[(int)new_py][(int)new_px] != '1')
// 	{
// 		player->px = new_px;
// 		player->py = new_py;
// 	}
// 	draw_map(player);
// }

// void	move_left(t_player *player)
// {
// 	float	new_px;
// 	float	new_py;

// 	new_px = player->px - player->dir_y * MOVE_SPEED;
// 	new_py = player->py + player->dir_x * MOVE_SPEED;
// 	if (player->map[(int)new_py][(int)new_px] != '1')
// 	{
// 		player->px = new_px;
// 		player->py = new_py;
// 	}
// 	draw_map(player);
// }

// void	move_right(t_player *player)
// {
// 	float	new_px;
// 	float	new_py;

// 	new_px = player->px + player->dir_y * MOVE_SPEED;
// 	new_py = player->py - player->dir_x * MOVE_SPEED;
// 	if (player->map[(int)new_py][(int)new_px] != '1')
// 	{
// 		player->px = new_px;
// 		player->py = new_py;
// 	}
// 	draw_map(player);
// }

// void	rotate_player(t_player *player, float angle)
// {
// 	float	old_dir_x;

// 	old_dir_x = player->dir_x;
// 	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
// 	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
// 	draw_map(player);
// }

// int	key_rotate(int keycode, void *param)
// {
// 	t_player	*player;

// 	player = (t_player *)param;
// 	if (keycode == 65361)
// 		rotate_player(player, -ROTATE_SPEED);
// 	else if (keycode == 65363)
// 		rotate_player(player, ROTATE_SPEED);
// 	return (0);
// }

// int	key_press(int keycode, void *params)
// {
// 	t_player	*player;

// 	player = (t_player *)params;
// 	if (keycode == 65307)
// 	{
//         mlx_destroy_image(player->mlx, player->mlx_bg);
// 		mlx_destroy_window(player->mlx, player->mlx_win);
// 		exit(0);
// 	}
// 	else if (keycode == 119 || keycode == 65362)
// 		move_forward(player);
// 	else if (keycode == 115 || keycode == 65364)
// 		move_backward(player);
// 	else if (keycode == 100)
// 		move_left(player);
// 	else if (keycode == 97)
// 		move_right(player);
// 	return (0);
// }

// int	main(void)
// {
// 	t_player	player;

// 	player.px = 4.5;
// 	player.py = 4.5;
// 	player.dir_x = -1;
// 	player.dir_y = 0;
// 	player.map = (char *[]){strdup("1111111111"), strdup("1000000001"),
// 		strdup("1000010001"), strdup("1000010001"), strdup("10000P0001"),
// 		strdup("1000010001"), strdup("1000010001"), strdup("1111111111"), NULL};
// 	player.mlx = mlx_init();
// 	player.mlx_win = mlx_new_window(player.mlx, 1000, 800, "2D Game");
// 	player.mlx_bg = mlx_xpm_file_to_image(player.mlx, "./black.xpm",
// 			&(int){1000}, &(int){800});
// 	draw_map1(&player);
// 	mlx_hook(player.mlx_win, 2, 1L << 0, key_press, &player);
// 	mlx_key_hook(player.mlx_win, key_rotate, &player);
// 	mlx_loop(player.mlx);
// 	return (0);
// }

#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOVE_SPEED 0.2
#define ROTATE_SPEED 0.15
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define MAP_SIZE 100

typedef struct s_player
{
	void    *mlx;
	void    *mlx_win;
	void    *mlx_bg;
	float   px;
	float   py;
	float   dir_x;
	float   dir_y;
	char    **map;
	int     map_width;
	int     map_height;
}           t_player;

void draw_line(void *mlx, void *mlx_win, int x0, int y0, int x1, int y1, int color, char **map)
{
	int dx, sx, dy, sy, err, e2;
	dx = abs(x1 - x0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	dy = abs(y1 - y0);
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	if (dx > dy)
		err = dx / 2;
	else
		err = -dy / 2;

	while (1)
	{
		if (map[y0 / MAP_SIZE][x0 / MAP_SIZE] == '1')
			break;
		mlx_pixel_put(mlx, mlx_win, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

// void draw_view_cone(void *mlx, void *mlx_win, int center_x, int center_y, double dir_x, double dir_y, double fov, int length, int color, char **map)
// {
// 	double half_fov, start_angle, end_angle, angle_increment, angle;
// 	int num_lines, i, end_x, end_y;

// 	half_fov = fov / 2.0;
// 	start_angle = atan2(dir_y, dir_x) - half_fov;
// 	end_angle = atan2(dir_y, dir_x) + half_fov;
// 	num_lines = 50;
// 	angle_increment = (end_angle - start_angle) / num_lines;
// 	i = 0;
// 	while (i <= num_lines)
// 	{
// 		angle = start_angle + i * angle_increment;
// 		end_x = center_x + (int)(cos(angle) * length);
// 		end_y = center_y + (int)(sin(angle) * length);
// 		draw_line(mlx, mlx_win, center_x, center_y, end_x, end_y, color, map);
// 		i++;
// 	}
// }

void draw_view_cone(void *mlx, void *mlx_win, int center_x, int center_y, double dir_x, double dir_y, double fov, int length, int color, char **map)
{
    double half_fov = fov / 2.0;
    double start_angle = atan2(dir_y, dir_x) - half_fov;
    double end_angle = atan2(dir_y, dir_x) + half_fov;
    int num_lines = 50;
    double angle_increment = (end_angle - start_angle) / num_lines;
    double cos_values[num_lines + 1];
    double sin_values[num_lines + 1];
    int i = 0;

    // Precompute cosine and sine values
    while (i <= num_lines)
    {
        double angle = start_angle + i * angle_increment;
        cos_values[i] = cos(angle);
        sin_values[i] = sin(angle);
        i++;
    }

    // Draw lines using precomputed values
    i = 0;
    while (i <= num_lines)
    {
        int end_x = center_x + (int)(cos_values[i] * length);
        int end_y = center_y + (int)(sin_values[i] * length);
        draw_line(mlx, mlx_win, center_x, center_y, end_x, end_y, color, map);
        i++;
    }
}

void draw_player(t_player *player)
{
	int radius, center_x, center_y, x, y;

	radius = 5;
	center_x = (int)(player->px * MAP_SIZE);
	center_y = (int)(player->py * MAP_SIZE);

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				mlx_pixel_put(player->mlx, player->mlx_win, center_x + x, center_y + y, 0x00FFFFFF);
			}
			x++;
		}
		y++;
	}

	draw_view_cone(player->mlx, player->mlx_win, center_x, center_y, player->dir_x, player->dir_y, M_PI / 3, 1000, 0x00FFFFFF, player->map);
}

void draw_map(t_player *player)
{
	static void *img = NULL;
	static int *img_data = NULL;
	static int bpp, size_line, endian;
	int i, j, y, x, pixel;

	if (!img)
	{
		img = mlx_new_image(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	}

	memset(img_data, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));

	i = 0;
	while (i < player->map_height)
	{
		j = 0;
		while (j < player->map_width)
		{
			if (player->map[i][j] == '1')
			{
				y = 0;
				while (y < MAP_SIZE)
				{
					x = 0;
					while (x < MAP_SIZE)
					{
						pixel = (i * MAP_SIZE + y) * WINDOW_WIDTH + (j * MAP_SIZE + x);
						if (x == 0 || x == MAP_SIZE - 1 || y == 0 || y == MAP_SIZE - 1)
							img_data[pixel] = 0x00FF00FF;
						else
							img_data[pixel] = 0x0000FF00;
						x++;
					}
					y++;
				}
			}
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(player->mlx, player->mlx_win, img, 0, 0);
	draw_player(player);
}

void move_player(t_player *player, float dx, float dy)
{
	float new_px, new_py;

	new_px = player->px + dx;
	new_py = player->py + dy;
	if (player->map[(int)new_py][(int)new_px] != '1')
	{
		player->px = new_px;
		player->py = new_py;
	}
	draw_map(player);
}

void rotate_player(t_player *player, float angle)
{
	float old_dir_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	draw_map(player);
}

int key_press(int keycode, void *params)
{
	t_player *player;
	int i;

	player = (t_player *)params;
	switch (keycode)
	{
		case 65307: // ESC
			mlx_destroy_image(player->mlx, player->mlx_bg);
			mlx_destroy_window(player->mlx, player->mlx_win);
			i = 0;
			while (player->map[i])
			{
				free(player->map[i]);
				i++;
			}
			exit(0);
		case 119: case 65362: // W or UP
			move_player(player, player->dir_x * MOVE_SPEED, player->dir_y * MOVE_SPEED);
			break;
		case 115: case 65364: // S or DOWN
			move_player(player, -player->dir_x * MOVE_SPEED, -player->dir_y * MOVE_SPEED);
			break;
		case 100: // D
			move_player(player, player->dir_y * MOVE_SPEED, -player->dir_x * MOVE_SPEED);
			break;
		case 97: // A
			move_player(player, -player->dir_y * MOVE_SPEED, player->dir_x * MOVE_SPEED);
			break;
		case 65361: // LEFT
			rotate_player(player, -ROTATE_SPEED);
			break;
		case 65363: // RIGHT
			rotate_player(player, ROTATE_SPEED);
			break;
	}
	return (0);
}

int main(void)
{
	t_player player;
	int map_width, map_height;

	player.px = 4.5;
	player.py = 4.5;
	player.dir_x = -1;
	player.dir_y = 0;
	player.map = (char *[]){
		strdup("1111111111"),
		strdup("1000000001"),
		strdup("1000010001"),
		strdup("1000010001"),
		strdup("10000P0001"),
		strdup("1000010001"),
		strdup("1000010001"),
		strdup("1111111111"),
		NULL
	};
	map_width = strlen(player.map[0]);
	map_height = 8;  // Count of non-NULL entries in player.map
	player.map_width = map_width;
	player.map_height = map_height;

	player.mlx = mlx_init();
	player.mlx_win = mlx_new_window(player.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "2D Game");
	player.mlx_bg = mlx_xpm_file_to_image(player.mlx, "./black.xpm", &(int){WINDOW_WIDTH}, &(int){WINDOW_HEIGHT});

	draw_map(&player);
	mlx_hook(player.mlx_win, 2, 1L << 0, key_press, &player);
	mlx_loop(player.mlx);

	return (0);
}