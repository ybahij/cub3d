
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOVE_SPEED 0.2
#define ROTATE_SPEED 0.2
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define MAP_SIZE 100
#define PI 3.14159265358979323846

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
	double	 angle;
	int			n_ray;
	void    *texture;      // Wall texture
    int     *texture_data;
    void    *screen_img;   // Buffer for 3D rendering
    int     *screen_data;
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

// double	const_ray(t_player *player, double angle)
// {

// }

// void	cast_all_ray(t_player *player)
// {
// 	int	columnid = 0;
// 	int i = -1;
// 	int ray;
// 	double rayangle = ROTATE_SPEED - (player->angle / 2);
// 	while (++i < player->n_ray)
// 	{
// 		const_ray(player, rayangle);

// 		rayangle += player->angle / player->n_ray;
// 	}
// }

// void		draw_3d_view(t_player *player)
// {
// 	int width, height, row, col, size, n_ray, wall_width, bpp, size_line, endian;
// 	float vew_angle;
// 	static void	*screen_img = NULL;
// 	static int *screen_data = NULL;

// 	if (!screen_img)
// 	{
// 		screen_img = mlx_new_image(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
// 		if (!screen_img)
// 				return;
// 		screen_data = (int *)mlx_get_data_addr(screen_img, &bpp, &size_line, &endian);
// 		if (!screen_data)
// 				return;
// 	}
// 	player->screen_img = screen_img;
// 	player->screen_data = screen_data;
// 	col = 10;
// 	player->angle = 60 * (PI / 180);
// 	row = 8;
// 	size = 100;
// 	width = 100 * col;
// 	height = 100 * row;
// 	wall_width = 4;
// 	player->n_ray = width / wall_width;
// 	cast_all_ray(player);

// }
void draw_3d_view(t_player *player)
{
    static void *screen_img = NULL;
    static int *screen_data = NULL;
    int bpp, size_line, endian;

    // Initialize screen buffer only once
    if (!screen_img)
    {
        screen_img = mlx_new_image(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
        if (!screen_img)
            return;
        screen_data = (int *)mlx_get_data_addr(screen_img, &bpp, &size_line, &endian);
        if (!screen_data)
            return;
    }

    // Pre-calculate constants
    const double half_height = WINDOW_HEIGHT / 2.0;
    const int screen_size = WINDOW_WIDTH * WINDOW_HEIGHT;

    // Clear screen buffer (using int pointer for faster clearing)
    int *end = screen_data + screen_size;
    int *ptr = screen_data;
    while (ptr < end)
        *ptr++ = 0;

    int x = 0;
    while (x < WINDOW_WIDTH)
    {
        // Optimize ray direction calculation
        const double camera_x = (2.0 * x / WINDOW_WIDTH) - 1;
        const double ray_dir_x = player->dir_x + player->dir_y * camera_x * 0.66;
        const double ray_dir_y = player->dir_y - player->dir_x * camera_x * 0.66;

        // Current map position
        int map_x = (int)player->px;
        int map_y = (int)player->py;

        // Optimize delta distance calculation
				double delta_dist_x, delta_dist_y;
				if (fabs(ray_dir_x) < 1e-8)
					delta_dist_x = 1e8;
				else
					delta_dist_x = fabs(1 / ray_dir_x);

				if (fabs(ray_dir_y) < 1e-8)
					delta_dist_y = 1e8;
				else
					delta_dist_y = fabs(1 / ray_dir_y);

        // Optimize step and side_dist calculation
        const int step_x = (ray_dir_x < 0) ? -1 : 1;
        const int step_y = (ray_dir_y < 0) ? -1 : 1;
        const double player_offset_x = (ray_dir_x < 0) ? player->px - map_x : map_x + 1.0 - player->px;
        const double player_offset_y = (ray_dir_y < 0) ? player->py - map_y : map_y + 1.0 - player->py;
        double side_dist_x = player_offset_x * delta_dist_x;
        double side_dist_y = player_offset_y * delta_dist_y;

        // DDA optimization
        int side = 0;
        while (1)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }

            if (map_y >= 0 && map_y < player->map_height &&
                map_x >= 0 && map_x < player->map_width &&
                player->map[map_y][map_x] == '1')
                break;
        }

        // Optimize wall distance calculation
        const double perp_wall_dist = (side == 0) ?
            (side_dist_x - delta_dist_x) : (side_dist_y - delta_dist_y);

        // Optimize line height calculation
        const int line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
        const int half_line = line_height >> 1;

        // Calculate drawing bounds
        int draw_start = (int)(-half_line + half_height);
        if (draw_start < 0)
            draw_start = 0;

        int draw_end = (int)(half_line + half_height);
        if (draw_end >= WINDOW_HEIGHT)
            draw_end = WINDOW_HEIGHT - 1;

        // Pre-calculate screen offset
        const int screen_offset = x;
        const int color = side ? 0x00FF0000 : 0x00CC0000;

        // Draw walls with optimized memory access
        int y = draw_start;
        int *column = screen_data + (y * WINDOW_WIDTH) + screen_offset;
        while (y < draw_end)
        {
            *column = color;
            column += WINDOW_WIDTH;
            y++;
        }

        // Draw ceiling
        y = 0;
        column = screen_data + screen_offset;
        while (y < draw_start)
        {
            *column = 0x00404040;
            column += WINDOW_WIDTH;
            y++;
        }

        // Draw floor
        column = screen_data + (draw_end * WINDOW_WIDTH) + screen_offset;
        while (y < WINDOW_HEIGHT)
        {
            *column = 0x00808080;
            column += WINDOW_WIDTH;
            y++;
        }

        x++;
    }

    // Put the rendered image to window
    if (screen_img)
        mlx_put_image_to_window(player->mlx, player->mlx_win, screen_img, 0, 0);
}

// void draw_3d_view(t_player *player)
// {
//     if (!player->screen_img) {
//         player->screen_img = mlx_new_image(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
//         player->screen_data = (int *)mlx_get_data_addr(player->screen_img, &(int){0}, &(int){0}, &(int){0});
//     }

//     // Clear screen buffer
//     memset(player->screen_data, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));

//     // Cast a ray for each column of the screen
//     for (int x = 0; x < WINDOW_WIDTH; x++) {
//         // Calculate ray position and direction
//         double camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
//         double ray_dir_x = player->dir_x + player->dir_y * camera_x * 0.66; // Adjust FOV
//         double ray_dir_y = player->dir_y - player->dir_x * camera_x * 0.66;

//         // Current map position
//         int map_x = (int)player->px;
//         int map_y = (int)player->py;

//         // Length of ray from current position to next x or y-side
//         double delta_dist_x = fabs(1 / ray_dir_x);
//         double delta_dist_y = fabs(1 / ray_dir_y);

//         // Calculate step and initial side_dist
//         int step_x;
//         int step_y;
//         double side_dist_x;
//         double side_dist_y;

//         if (ray_dir_x < 0) {
//             step_x = -1;
//             side_dist_x = (player->px - map_x) * delta_dist_x;
//         } else {
//             step_x = 1;
//             side_dist_x = (map_x + 1.0 - player->px) * delta_dist_x;
//         }
//         if (ray_dir_y < 0) {
//             step_y = -1;
//             side_dist_y = (player->py - map_y) * delta_dist_y;
//         } else {
//             step_y = 1;
//             side_dist_y = (map_y + 1.0 - player->py) * delta_dist_y;
//         }

//         // Perform DDA (Digital Differential Analysis)
//         int hit = 0;
//         int side; // 0 for x-side, 1 for y-side
//         while (hit == 0) {
//             if (side_dist_x < side_dist_y) {
//                 side_dist_x += delta_dist_x;
//                 map_x += step_x;
//                 side = 0;
//             } else {
//                 side_dist_y += delta_dist_y;
//                 map_y += step_y;
//                 side = 1;
//             }
//             if (player->map[map_y][map_x] == '1')
//                 hit = 1;
//         }

//         // Calculate distance to the wall
//         double perp_wall_dist;
//         if (side == 0)
//             perp_wall_dist = (map_x - player->px + (1 - step_x) / 2) / ray_dir_x;
//         else
//             perp_wall_dist = (map_y - player->py + (1 - step_y) / 2) / ray_dir_y;

//         // Calculate wall height
//         int line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
//         int draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
//         if (draw_start < 0)
//             draw_start = 0;
//         int draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
//         if (draw_end >= WINDOW_HEIGHT)
//             draw_end = WINDOW_HEIGHT - 1;

//         // Choose wall color based on side
//         int color = side == 1 ? 0x00FF0000 : 0x00CC0000;

//         // Draw the vertical line
//         for (int y = draw_start; y < draw_end; y++) {
//             player->screen_data[y * WINDOW_WIDTH + x] = color;
//         }

//         // Draw floor and ceiling
//         for (int y = 0; y < draw_start; y++)
//             player->screen_data[y * WINDOW_WIDTH + x] = 0x00404040; // Ceiling
//         for (int y = draw_end; y < WINDOW_HEIGHT; y++)
//             player->screen_data[y * WINDOW_WIDTH + x] = 0x00808080; // Floor
//     }

//     // Put the rendered image to window
//     mlx_put_image_to_window(player->mlx, player->mlx_win, player->screen_img, 0, 0);
// }

// void cast_rays(void *mlx, void *mlx_win, int x0, int y0, int x1, int y1, int color, char **map, t_player *player)
// {
// 	// mlx_clear_window(mlx, mlx_win);
// 	int i, j;
// 	for (i = 0; i < player->map_height; i++)
// 	{
// 		for (j = 0; j < player->map_width; j++)
// 		{
// 			if (i >= 0 && i < player->map_height && j >= 0 && j < player->map_width && player->map[i][j] == '1')
// 			{
// 				int x0 = j * MAP_SIZE;
// 				int y0 = i * MAP_SIZE;
// 				int x1 = x0 + MAP_SIZE;
// 				int y1 = y0;
// 				int x2 = x1;
// 				int y2 = y1 + MAP_SIZE;
// 				int x3 = x0;
// 				int y3 = y2;
// 				draw_line(mlx, mlx_win, x0, y0, x1, y1, 0x00FFFFFF, player->map);
// 				draw_line(mlx, mlx_win, x1, y1, x2, y2, 0x00FFFFFF, player->map);
// 				draw_line(mlx, mlx_win, x2, y2, x3, y3, 0x00FFFFFF, player->map);
// 				draw_line(mlx, mlx_win, x3, y3, x0, y0, 0x00FFFFFF, player->map);
// 			}
// 		}
// 	}
// }


// void draw_view_cone(void *mlx, void *mlx_win, int center_x, int center_y, double dir_x, double dir_y, double fov, int length, int color, char **map, t_player *player)
// {
//     double half_fov = fov / 2.0;
//     double start_angle = atan2(dir_y, dir_x) - half_fov;
//     double end_angle = atan2(dir_y, dir_x) + half_fov;
//     int num_lines = 50;
//     double angle_increment = (end_angle - start_angle) / num_lines;
//     double cos_values[num_lines + 1];
//     double sin_values[num_lines + 1];
//     int i = 0;

//     while (i <= num_lines)
//     {
//         double angle = start_angle + i * angle_increment;
//         cos_values[i] = cos(angle);
//         sin_values[i] = sin(angle);
//         i++;
//     }

//     // i = 0;
//     // while (i <= num_lines)
//     // {
//     //     int end_x = center_x + (int)(cos_values[i] * length);
//     //     int end_y = center_y + (int)(sin_values[i] * length);
//     //     // draw_line(mlx, mlx_win, center_x, center_y, end_x, end_y, color, map);
// 	// 	i++;
//     // }
//     draw_3d_view(player);
// }

// void draw_player(t_player *player)
// {
// 	int radius, center_x, center_y, x, y;

// 	radius = 5;
// 	center_x = (int)(player->px * MAP_SIZE);
// 	center_y = (int)(player->py * MAP_SIZE);

// 	y = -radius;
// 	while (y <= radius)
// 	{
// 		x = -radius;
// 		while (x <= radius)
// 		{
// 			if (x * x + y * y <= radius * radius)
// 			{
// 				mlx_pixel_put(player->mlx, player->mlx_win, center_x + x, center_y + y, 0x00FFFFFF);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}

// 	draw_view_cone(player->mlx, player->mlx_win, center_x, center_y, player->dir_x, player->dir_y, M_PI / 3, 1000, 0x00FFFFFF, player->map, player);
// }

// void draw_map(t_player *player)
// {
// 	static void *img = NULL;
// 	static int *img_data = NULL;
// 	static int bpp, size_line, endian;
// 	int i, j, y, x, pixel;

// 	if (!img)
// 	{
// 		img = mlx_new_image(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
// 		img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
// 	}

// 	memset(img_data, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));

// 	i = 0;
// 	while (i < player->map_height)
// 	{
// 		j = 0;
// 		while (j < player->map_width)
// 		{
// 			if (player->map[i][j] == '1')
// 			{
// 				y = 0;
// 				while (y < MAP_SIZE)
// 				{
// 					x = 0;
// 					while (x < MAP_SIZE)
// 					{
// 						pixel = (i * MAP_SIZE + y) * WINDOW_WIDTH + (j * MAP_SIZE + x);
// 						if (x == 0 || x == MAP_SIZE - 1 || y == 0 || y == MAP_SIZE - 1)
// 							img_data[pixel] = 0x00FF00FF;
// 						else
// 							img_data[pixel] = 0x0000FF00;
// 						x++;
// 					}
// 					y++;
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}

// 	mlx_put_image_to_window(player->mlx, player->mlx_win, img, 0, 0);
// 	draw_player(player);
// }

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
    draw_3d_view(player);
	// draw_map(player);
}

void rotate_player(t_player *player, float angle)
{
	float old_dir_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	// draw_map(player);
    draw_3d_view(player);

}

int key_press(int keycode, void *params)
{
	t_player *player;
	int i;

	player = (t_player *)params;
	if (keycode == 65307) // ESC
	{
		mlx_destroy_image(player->mlx, player->mlx_bg);
		mlx_destroy_window(player->mlx, player->mlx_win);
		int i = 0;
		while (player->map[i])
		{
			free(player->map[i]);
			i++;
		}
		exit(0);
	}
	else if (keycode == 119 || keycode == 65362)
	{
		move_player(player, player->dir_x * MOVE_SPEED, player->dir_y * MOVE_SPEED);
	}
	else if (keycode == 115 || keycode == 65364) // S or DOWN
	{
		move_player(player, -player->dir_x * MOVE_SPEED, -player->dir_y * MOVE_SPEED);
	}
	else if (keycode == 100) // D
	{
		move_player(player, player->dir_y * MOVE_SPEED, -player->dir_x * MOVE_SPEED);
	}
	else if (keycode == 97) // A
	{
		move_player(player, -player->dir_y * MOVE_SPEED, player->dir_x * MOVE_SPEED);
	}
	else if (keycode == 65361) // LEFT
	{
		rotate_player(player, ROTATE_SPEED);
	}
	else if (keycode == 65363) // RIGHT
	{
		rotate_player(player, -ROTATE_SPEED);
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
	// player.angle = ;
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

	// draw_map(&player);
	draw_3d_view(&player);
	mlx_hook(player.mlx_win, 2, 1L << 0, key_press, &player);
	mlx_loop(player.mlx);

	return (0);
}