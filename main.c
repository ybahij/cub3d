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

// void draw_line(void *mlx, void *mlx_win, int x0, int y0, int x1, int y1, int color, char **map)
// {
// 	int dx, sx, dy, sy, err, e2;
// 	dx = abs(x1 - x0);
// 	if (x0 < x1)
// 		sx = 1;
// 	else
// 		sx = -1;
// 	dy = abs(y1 - y0);
// 	if (y0 < y1)
// 		sy = 1;
// 	else
// 		sy = -1;
// 	if (dx > dy)
// 		err = dx / 2;
// 	else
// 		err = -dy / 2;

// 	while (1)
// 	{
// 		if (map[y0 / MAP_SIZE][x0 / MAP_SIZE] == '1')
// 			break;
// 		mlx_pixel_put(mlx, mlx_win, x0, y0, color);
// 		if (x0 == x1 && y0 == y1)
// 			break;
// 		e2 = err;
// 		if (e2 > -dx)
// 		{
// 			err -= dy;
// 			x0 += sx;
// 		}
// 		if (e2 < dy)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }

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


// void draw_3d_view(t_player *player) {
//     int color;
//     static void *img = NULL;
//     static int *img_data = NULL;
//     int bpp, size_line, endian, map_x, map_y, step_x, step_y, side, hit, line_height, draw_start, draw_end, y, x;
//     double angle_increment, ray_angle, ray_dir_x, ray_dir_y, delta_dist_x, delta_dist_y, side_dist_x, side_dist_y, perp_wall_dist;

//     if (!img) {
//         img = mlx_new_image(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
//         img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
//     }
//     memset(img_data, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));

//     // Define the angle increment based on field of view
//     angle_increment = FOV / WINDOW_WIDTH;

//     x = 0;
//     while (x < WINDOW_WIDTH) {
//         // Calculate the ray angle relative to the player's direction
//         ray_angle = player->angle - (FOV / 2) + x * angle_increment;

//         // Calculate ray direction based on angle
//         ray_dir_x = cos(ray_angle);
//         ray_dir_y = sin(ray_angle);

//         // Map position (grid)
//         map_x = (int)player->px;
//         map_y = (int)player->py;

//         // Calculate delta distances for x and y
//         delta_dist_x = fabs(1 / ray_dir_x);
//         delta_dist_y = fabs(1 / ray_dir_y);

//         // Calculate step direction and initial side distances
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

//         // Perform DDA algorithm
//         hit = 0;
// 				while (hit == 0) {
// 					if (side_dist_x < side_dist_y) {
// 						side_dist_x += delta_dist_x;
// 						map_x += step_x;
// 						side = 0;
// 					} else {
// 						side_dist_y += delta_dist_y;
// 						map_y += step_y;
// 						side = 1;
// 					}
// 					if (player->map[map_y][map_x] == '1')
// 						hit = 1;
// 				}

//         // Calculate perpendicular wall distance with fisheye correction
//         if (side == 0)
//             perp_wall_dist = (map_x - player->px + (1 - step_x) / 2) / ray_dir_x;
//         else
//             perp_wall_dist = (map_y - player->py + (1 - step_y) / 2) / ray_dir_y;

//         perp_wall_dist *= cos(player->angle - ray_angle);

//         line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
//         draw_start =  WINDOW_HEIGHT / 2 -line_height / 2;
//         if (draw_start < 0) draw_start = 0;
//         draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
//         if (draw_end >= WINDOW_HEIGHT) draw_end = WINDOW_HEIGHT - 1;

// 				if (side == 1) {
// 					color = 0x00FF0000;
// 				} else {
// 					color = 0x00CC0000;
// 				}

//         // Draw vertical line for the wall slice
// 				y = draw_start;
// 				while (y < draw_end) {
// 					img_data[y * WINDOW_WIDTH + x] = color;
// 					y++;
// 				}

//         // Ceiling and floor coloring
// 				y = 0;
// 				while (y < draw_start) {
// 					img_data[y * WINDOW_WIDTH + x] = 0x00404040; // Ceiling color
// 					y++;
// 				}
// 				y = draw_end;
// 				while (y < WINDOW_HEIGHT) {
// 					img_data[y * WINDOW_WIDTH + x] = 0x00808080; // Floor color
// 					y++;
// 				}
//         x++;
//     }
//     player->screen_img = img;
//     mlx_put_image_to_window(player->mlx, player->mlx_win, img, 0, 0);
// }

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
#define FOV 60 * (PI / 180)

typedef struct s_texture {
    void *img;
    int *data;
    int width;
    int height;
} t_texture;
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
    t_texture north_texture;
    t_texture south_texture;
    t_texture west_texture;
    t_texture east_texture;
    void    *screen_img;   // Buffer for 3D rendering
    int     *screen_data;
}           t_player;



void draw_3d_view(t_player *player) {
    int color;
    static void *img = NULL;
    static int *img_data = NULL;
    static t_texture north_texture;
    static t_texture south_texture;
    static t_texture west_texture;
    static t_texture east_texture;
    int bpp, size_line, endian, map_x, map_y, step_x, step_y, side, hit, line_height, draw_start, draw_end, y, x;
    double angle_increment, ray_angle, ray_dir_x, ray_dir_y, delta_dist_x, delta_dist_y, side_dist_x, side_dist_y, perp_wall_dist;

    if (!img) {
        img = mlx_new_image(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
        img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);

        // Load textures
        north_texture.img = mlx_xpm_file_to_image(player->mlx, "./north.xpm", &north_texture.width, &north_texture.height);
        if (!north_texture.img) {
            printf("Failed to load north_texture.img\n");
            exit(1);
        }
        north_texture.data = (int *)mlx_get_data_addr(north_texture.img, &bpp, &size_line, &endian);

        south_texture.img = mlx_xpm_file_to_image(player->mlx, "./south.xpm", &south_texture.width, &south_texture.height);
        if (!south_texture.img) {
            printf("Failed to load south_texture.img\n");
            exit(1);
        }
        south_texture.data = (int *)mlx_get_data_addr(south_texture.img, &bpp, &size_line, &endian);

        west_texture.img = mlx_xpm_file_to_image(player->mlx, "./west.xpm", &west_texture.width, &west_texture.height);
        if (!west_texture.img) {
            printf("Failed to load west_texture.img\n");
            exit(1);
        }
        west_texture.data = (int *)mlx_get_data_addr(west_texture.img, &bpp, &size_line, &endian);

        east_texture.img = mlx_xpm_file_to_image(player->mlx, "./east.xpm", &east_texture.width, &east_texture.height);
        if (!east_texture.img) {
            printf("Failed to load east_texture.img\n");
            exit(1);
        }
        east_texture.data = (int *)mlx_get_data_addr(east_texture.img, &bpp, &size_line, &endian);
    }
    player->north_texture = north_texture;
    player->south_texture = south_texture;
    player->west_texture = west_texture;
    player->east_texture = east_texture;
    memset(img_data, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));

    // Define the angle increment based on field of view
    angle_increment = FOV / WINDOW_WIDTH;

    x = 0;
    while (x < WINDOW_WIDTH) {
        // Calculate the ray angle relative to the player's direction
        ray_angle = player->angle - (FOV / 2) + x * angle_increment;

        // Calculate ray direction based on angle
        ray_dir_x = cos(ray_angle);
        ray_dir_y = sin(ray_angle);

        // Map position (grid)
        map_x = (int)player->px;
        map_y = (int)player->py;

        // Calculate delta distances for x and y
        delta_dist_x = fabs(1 / ray_dir_x);
        delta_dist_y = fabs(1 / ray_dir_y);

        // Calculate step direction and initial side distances
        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (player->px - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - player->px) * delta_dist_x;
        }
        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (player->py - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - player->py) * delta_dist_y;
        }

        // Perform DDA algorithm
        hit = 0;
        while (hit == 0) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (player->map[map_y][map_x] == '1')
                hit = 1;
        }

        // Calculate perpendicular wall distance with fisheye correction
        if (side == 0)
            perp_wall_dist = (map_x - player->px + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - player->py + (1 - step_y) / 2) / ray_dir_y;

        perp_wall_dist *= cos(player->angle - ray_angle);

        line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
        draw_start = WINDOW_HEIGHT / 2 - line_height / 2;
        if (draw_start < 0) draw_start = 0;
        draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_end >= WINDOW_HEIGHT)
					draw_end = WINDOW_HEIGHT - 1;

        t_texture *texture;
        if (side == 0) {
            if (ray_dir_x > 0)
                texture = &west_texture;
            else
                texture = &east_texture;
        } else {
            if (ray_dir_y > 0)
                texture = &north_texture;
            else
                texture = &south_texture;
        }

        // Draw vertical line for the wall slice using texture
        y = draw_start;
        int tex_x;
        int tex_y;
        double wall_hit;
        if (side == 0) {
            double wall_hit = player->py + perp_wall_dist * ray_dir_y;
            wall_hit -= floor(wall_hit);
            tex_x = (int)(wall_hit * texture->width);
        } else {
            wall_hit = player->px + perp_wall_dist * ray_dir_x;
            wall_hit -= floor(wall_hit);
            tex_x = (int)(wall_hit * texture->width);
        }
        while (y < draw_end) {
            tex_y = (y - draw_start) * texture->height / line_height;
            color = texture->data[tex_y * texture->width + tex_x];
            img_data[y * WINDOW_WIDTH + x] = color;
            y++;
        }

        // Ceiling and floor coloring
        y = 0;
        while (y < draw_start) {
            img_data[y * WINDOW_WIDTH + x] = 0x00404040; // Ceiling color
            y++;
        }
        y = draw_end;
        while (y < WINDOW_HEIGHT) {
            img_data[y * WINDOW_WIDTH + x] = 0x00808080; // Floor color
            y++;
        }
        x++;
    }
    player->screen_img = img;
    mlx_put_image_to_window(player->mlx, player->mlx_win, img, 0, 0);
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
	else
	{
		if (player->map[(int)player->py][(int)new_px] != '1')
			player->px = new_px;
		else if (player->map[(int)new_py][(int)player->px] != '1')
			player->py = new_py;
	}
	draw_3d_view(player);
	// draw_map(player);
}

void rotate_player(t_player *player, float angle)
{
	float old_dir_x;

	player->angle += angle;
	if (player->angle < 0) player->angle += 2 * PI;      // Keep angle within 0 to 2*PI
	if (player->angle >= 2 * PI) player->angle -= 2 * PI;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	// draw_map(player);
    draw_3d_view(player);

}

int close_window(void *params)
{
    t_player *player;

    player = (t_player *)params;
    mlx_destroy_image(player->mlx, player->screen_img);
    mlx_destroy_image(player->mlx, player->north_texture.img);
    mlx_destroy_image(player->mlx, player->south_texture.img);
    mlx_destroy_image(player->mlx, player->west_texture.img);
    mlx_destroy_image(player->mlx, player->east_texture.img);
    mlx_destroy_window(player->mlx, player->mlx_win);
    int i = 0;
    while (player->map[i])
    {
        free(player->map[i]);
        i++;
    }
    exit(0);
}
int key_press(int keycode, void *params)
{
	t_player *player;
	int i;

	player = (t_player *)params;
	if (keycode == 65307) // ESC
        close_window(player);
	else if (keycode == 119 || keycode == 65362)
	{
		move_player(player, -player->dir_x * MOVE_SPEED, -player->dir_y * MOVE_SPEED);
	}
	else if (keycode == 115 || keycode == 65364) // S or DOWN
	{
		move_player(player, player->dir_x * MOVE_SPEED, player->dir_y * MOVE_SPEED);
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
		rotate_player(player, -ROTATE_SPEED);
	}
	else if (keycode == 65363) // RIGHT
	{
		rotate_player(player, ROTATE_SPEED);
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
	player.angle = -ROTATE_SPEED;
	player.map = (char *[]){
		strdup("1111111111111111111111"),
		strdup("10000000000001000000001"),
		strdup("10000100011111011111111"),
		strdup("10000100000000001"),
		strdup("10000P00011111111"),
		strdup("10000100000000001"),
		strdup("10000100000000001"),
		strdup("11111111111111111"),
		NULL
	};
	map_width = strlen(player.map[0]);
	map_height = 8;  // Count of non-NULL entries in player.map
	player.map_width = map_width;
	player.map_height = map_height;

	player.mlx = mlx_init();
	player.mlx_win = mlx_new_window(player.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "2D Game");
	// player.mlx_bg = mlx_xpm_file_to_image(player.mlx, "./black.xpm", &(int){WINDOW_WIDTH}, &(int){WINDOW_HEIGHT});

	// draw_map(&player);
	draw_3d_view(&player);
	mlx_hook(player.mlx_win, 2, 1L << 0, key_press, &player);
    mlx_hook(player.mlx_win, 17, 0, close_window, &player);
	mlx_loop(player.mlx);

	return (0);
}