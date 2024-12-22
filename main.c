// // void draw_view_cone(void *mlx, void *mlx_win, int center_x, int center_y,
// 	double dir_x, double dir_y, double fov, int length, int color, char **map,
// 	t_player *player)
// // {
// //     double half_fov = fov / 2.0;
// //     double start_angle = atan2(dir_y, dir_x) - half_fov;
// //     double end_angle = atan2(dir_y, dir_x) + half_fov;
// //     int num_lines = 50;
// //     double angle_increment = (end_angle - start_angle) / num_lines;
// //     double cos_values[num_lines + 1];
// //     double sin_values[num_lines + 1];
// //     int i = 0;

// //     while (i <= num_lines)
// //     {
// //         double angle = start_angle + i * angle_increment;
// //         cos_values[i] = cos(angle);
// //         sin_values[i] = sin(angle);
// //         i++;
// //     }

// //     // i = 0;
// //     // while (i <= num_lines)
// //     // {
// //     //     int end_x = center_x + (int)(cos_values[i] * length);
// //     //     int end_y = center_y + (int)(sin_values[i] * length);
// //     //     // draw_line(mlx, mlx_win, center_x, center_y, end_x, end_y,
// 	color, map);
// // 	// 	i++;
// //     // }
// //     draw_3d_view(player);
// // }

// // void draw_player(t_player *player)
// // {
// // 	int radius, center_x, center_y, x, y;

// // 	radius = 5;
// // 	center_x = (int)(player->px * MAP_SIZE);
// // 	center_y = (int)(player->py * MAP_SIZE);

// // 	y = -radius;
// // 	while (y <= radius)
// // 	{
// // 		x = -radius;
// // 		while (x <= radius)
// // 		{
// // 			if (x * x + y * y <= radius * radius)
// // 			{
// // 				mlx_pixel_put(player->mlx, player->mlx_win, center_x + x,
// 					center_y + y, 0x00FFFFFF);
// // 			}
// // 			x++;
// // 		}
// // 		y++;
// // 	}

// // 	draw_view_cone(player->mlx, player->mlx_win, center_x, center_y,
// 		player->dir_x, player->dir_y, M_PI / 3, 1000, 0x00FFFFFF, player->map,
// 		player);
// // }

// // void draw_map(t_player *player)
// // {
// // 	static void *img = NULL;
// // 	static int *img_data = NULL;
// // 	static int bpp, size_line, endian;
// // 	int i, j, y, x, pixel;

// // 	if (!img)
// // 	{
// // 		img = mlx_new_image(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
// // 		img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
// // 	}

// // 	memset(img_data, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));

// // 	i = 0;
// // 	while (i < player->map_height)
// // 	{
// // 		j = 0;
// // 		while (j < player->map_width)
// // 		{
// // 			if (player->map[i][j] == '1')
// // 			{
// // 				y = 0;
// // 				while (y < MAP_SIZE)
// // 				{
// // 					x = 0;
// // 					while (x < MAP_SIZE)
// // 					{
// // 						pixel = (i * MAP_SIZE + y) * WINDOW_WIDTH + (j
// 								* MAP_SIZE + x);
// // 						if (x == 0 || x == MAP_SIZE - 1 || y == 0
// 							|| y == MAP_SIZE - 1)
// // 							img_data[pixel] = 0x00FF00FF;
// // 						else
// // 							img_data[pixel] = 0x0000FF00;
// // 						x++;
// // 					}
// // 					y++;
// // 				}
// // 			}
// // 			j++;
// // 		}
// // 		i++;
// // 	}

// // 	mlx_put_image_to_window(player->mlx, player->mlx_win, img, 0, 0);
// // 	draw_player(player);
// // }

// // void draw_line(void *mlx, void *mlx_win, int x0, int y0, int x1, int y1,
// 	int color, char **map)
// // {
// // 	int dx, sx, dy, sy, err, e2;
// // 	dx = abs(x1 - x0);
// // 	if (x0 < x1)
// // 		sx = 1;
// // 	else
// // 		sx = -1;
// // 	dy = abs(y1 - y0);
// // 	if (y0 < y1)
// // 		sy = 1;
// // 	else
// // 		sy = -1;
// // 	if (dx > dy)
// // 		err = dx / 2;
// // 	else
// // 		err = -dy / 2;

// // 	while (1)
// // 	{
// // 		if (map[y0 / MAP_SIZE][x0 / MAP_SIZE] == '1')
// // 			break ;
// // 		mlx_pixel_put(mlx, mlx_win, x0, y0, color);
// // 		if (x0 == x1 && y0 == y1)
// // 			break ;
// // 		e2 = err;
// // 		if (e2 > -dx)
// // 		{
// // 			err -= dy;
// // 			x0 += sx;
// // 		}
// // 		if (e2 < dy)
// // 		{
// // 			err += dx;
// // 			y0 += sy;
// // 		}
// // 	}
// // }

// // double	const_ray(t_player *player, double angle)
// // {

// // }

// // void	cast_all_ray(t_player *player)
// // {
// // 	int	columnid = 0;
// // 	int i = -1;
// // 	int ray;
// // 	double rayangle = ROTATE_SPEED - (player->angle / 2);
// // 	while (++i < player->n_ray)
// // 	{
// // 		const_ray(player, rayangle);

// // 		rayangle += player->angle / player->n_ray;
// // 	}
// // }

// // void		draw_3d_view(t_player *player)
// // {
// // 	int width, height, row, col, size, n_ray, wall_width, bpp, size_line,
// 		endian;
// // 	float vew_angle;
// // 	static void	*screen_img = NULL;
// // 	static int *screen_data = NULL;

// // 	if (!screen_img)
// // 	{
// // 		screen_img = mlx_new_image(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
// // 		if (!screen_img)
// // 				return ;
// // 		screen_data = (int *)mlx_get_data_addr(screen_img, &bpp, &size_line,
// 				&endian);
// // 		if (!screen_data)
// // 				return ;
// // 	}
// // 	player->screen_img = screen_img;
// // 	player->screen_data = screen_data;
// // 	col = 10;
// // 	player->angle = 60 * (PI / 180);
// // 	row = 8;
// // 	size = 100;
// // 	width = 100 * col;
// // 	height = 100 * row;
// // 	wall_width = 4;
// // 	player->n_ray = width / wall_width;
// // 	cast_all_ray(player);

// // void draw_3d_view(t_player *player) {
// //     int color;
// //     static void *img = NULL;
// //     static int *img_data = NULL;
// //     int bpp, size_line, endian, map_x, map_y, step_x, step_y, side, hit,
// 	line_height, draw_start, draw_end, y, x;
// //     double angle_increment, ray_angle, ray_dir_x, ray_dir_y, delta_dist_x,
// 	delta_dist_y, side_dist_x, side_dist_y, perp_wall_dist;

// //     if (!img) {
// //         img = mlx_new_image(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
// //         img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
// //     }
// //     memset(img_data, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));

// //     // Define the angle increment based on field of view
// //     angle_increment = FOV / WINDOW_WIDTH;

// //     x = 0;
// //     while (x < WINDOW_WIDTH) {
// //         // Calculate the ray angle relative to the player's direction
// //         ray_angle = player->angle - (FOV / 2) + x * angle_increment;

// //         // Calculate ray direction based on angle
// //         ray_dir_x = cos(ray_angle);
// //         ray_dir_y = sin(ray_angle);

// //         // Map position (grid)
// //         map_x = (int)player->px;
// //         map_y = (int)player->py;

// //         // Calculate delta distances for x and y
// //         delta_dist_x = fabs(1 / ray_dir_x);
// //         delta_dist_y = fabs(1 / ray_dir_y);

// //         // Calculate step direction and initial side distances
// //         if (ray_dir_x < 0) {
// //             step_x = -1;
// //             side_dist_x = (player->px - map_x) * delta_dist_x;
// //         } else {
// //             step_x = 1;
// //             side_dist_x = (map_x + 1.0 - player->px) * delta_dist_x;
// //         }
// //         if (ray_dir_y < 0) {
// //             step_y = -1;
// //             side_dist_y = (player->py - map_y) * delta_dist_y;
// //         } else {
// //             step_y = 1;
// //             side_dist_y = (map_y + 1.0 - player->py) * delta_dist_y;
// //         }

// //         // Perform DDA algorithm
// //         hit = 0;
// // 				while (hit == 0) {
// // 					if (side_dist_x < side_dist_y) {
// // 						side_dist_x += delta_dist_x;
// // 						map_x += step_x;
// // 						side = 0;
// // 					} else {
// // 						side_dist_y += delta_dist_y;
// // 						map_y += step_y;
// // 						side = 1;
// // 					}
// // 					if (player->map[map_y][map_x] == '1')
// // 						hit = 1;
// // 				}

// //         // Calculate perpendicular wall distance with fisheye correction
// //         if (side == 0)
// //             perp_wall_dist = (map_x - player->px + (1 - step_x) / 2)
// 	/ ray_dir_x;
// //         else
// //             perp_wall_dist = (map_y - player->py + (1 - step_y) / 2)
// 	/ ray_dir_y;

// //         perp_wall_dist *= cos(player->angle - ray_angle);

// //         line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
// //         draw_start =  WINDOW_HEIGHT / 2 -line_height / 2;
// //         if (draw_start < 0) draw_start = 0;
// //         draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
// //         if (draw_end >= WINDOW_HEIGHT) draw_end = WINDOW_HEIGHT - 1;

// // 				if (side == 1) {
// // 					color = 0x00FF0000;
// // 				} else {
// // 					color = 0x00CC0000;
// // 				}

// //         // Draw vertical line for the wall slice
// // 				y = draw_start;
// // 				while (y < draw_end) {
// // 					img_data[y * WINDOW_WIDTH + x] = color;
// // 					y++;
// // 				}

// //         // Ceiling and floor coloring
// // 				y = 0;
// // 				while (y < draw_start) {
// // 					img_data[y * WINDOW_WIDTH + x] = 0x00404040;
// 						// Ceiling color
// // 					y++;
// // 				}
// // 				y = draw_end;
// // 				while (y < WINDOW_HEIGHT) {
// // 					img_data[y * WINDOW_WIDTH + x] = 0x00808080; // Floor color
// // 					y++;
// // 				}
// //         x++;
// //     }
// //     player->screen_img = img;
// //     mlx_put_image_to_window(player->mlx, player->mlx_win, img, 0, 0);
// // }

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


typedef struct s_texture
{
	void		*img;
	int			*data;
	int			width;
	int			height;
}				t_texture;
typedef struct s_player
{
	void		*mlx;
	void		*mlx_win;
	void		*mlx_bg;
	float		px;
	float		py;
	float		dir_x;
	float		dir_y;
	int 		floor_color;
	int 		ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;
	double		angle;
	char		start_angle;
	int			n_ray;
	void *texture;
	double wall_hit, angle_increment, ray_angle, ray_dir_x, ray_dir_y,
		delta_dist_x, delta_dist_y, side_dist_x, side_dist_y, perp_wall_dist;
	int map_x, map_y, step_x, step_y, side, hit, line_height, draw_start
		, draw_end, y, x;
	t_texture	*north_texture;
	t_texture	*south_texture;
	t_texture	*west_texture;
	t_texture	*east_texture;
	
	void *screen_img;
	int			*screen_data;
}				t_player;

typedef struct s_garbage
{
	void	*ptr;
	struct s_garbage	*next;
}				t_garbage;

int close_window(void *params);


t_garbage **ft_garbage(void)
{
    static t_garbage *garbage = NULL;
    return &garbage;
}


void garbage_collector(void)
{
    t_garbage **garbage = ft_garbage();
    t_garbage *current = *garbage;

    while (current)
    {
        t_garbage *next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    *garbage = NULL;
}

void ft_add_garbage(void *ptr)
{
    t_garbage **garbage = ft_garbage();
    t_garbage *new_garbage = malloc(sizeof(t_garbage));

    if (!new_garbage)
    {
        printf("Failed to allocate memory for garbage collector\n");
        garbage_collector();
        exit(1);
    }
    new_garbage->ptr = ptr;
    new_garbage->next = NULL;

    if (*garbage == NULL)
        *garbage = new_garbage;
    else
    {
        t_garbage *last = *garbage;
        while (last->next != NULL)
            last = last->next;
        last->next = new_garbage;
    }
}



void	*ft_malloc(size_t size)
{
	void	*ptr = malloc(size);
	
	if (!ptr)
	{
		printf("Failed to allocate memory\n");
		garbage_collector();
		exit(1);
	}
	ft_add_garbage(ptr);
	return (ptr);
}


int ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void load_texter(t_texture *texture, t_player *player, char *path)
{
	int bpp, size_line, endian;

	texture->img = mlx_xpm_file_to_image(player->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
	{
		printf("Failed to load texture\n");
		close_window(player);
		exit(1);
	}
	texture->data = (int *)mlx_get_data_addr(texture->img, &bpp,
			&size_line, &endian);
	
}

void	load_textures(t_player *player)
{
	player->north_texture = NULL;
	player->south_texture = NULL;
	player->west_texture = NULL;
	player->east_texture = NULL;
	player->north_texture = ft_malloc(sizeof(t_texture));
	load_texter(player->north_texture, player, "nort.xpm");
	player->south_texture = ft_malloc(sizeof(t_texture));
	load_texter(player->south_texture, player, "south.xpm");
	player->west_texture  = ft_malloc(sizeof(t_texture));
	load_texter(player->west_texture, player, "west.xpm");
	player->east_texture  = ft_malloc(sizeof(t_texture));
	load_texter(player->east_texture, player, "east.xpm");
}

void	set_img(t_player *player)
{
	static void			*img = NULL;
	static int			*img_data = NULL;
	int bpp, size_line, endian;

	if (!img)
	{
		img = mlx_new_image(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	}
	player->screen_img = img;
	player->screen_data = img_data;
	memset(img_data, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));
}

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

t_texture	*set_texter(t_player *player, t_texture *texture)
{		
	if (player->side == 0)
	{
		if (player->ray_dir_x > 0)
			return (player->west_texture);
		else
			return (player->east_texture);
	}
	else
	{
		if (player->ray_dir_y > 0)
			return (player->north_texture);
		else
			return (player->south_texture);
	}
}

void	draw_texture(t_player *player, t_texture *texture)
{
	int tex_x;
	int tex_y;
	int		color;

	player->y = player->draw_start;
	if (player->side == 0)
	{
		player->wall_hit = player->py + player->perp_wall_dist * player->ray_dir_y;
		player->wall_hit -= floor(player->wall_hit);
		tex_x = (int)(player->wall_hit * texture->width);
	}
	else
	{
		player->wall_hit = player->px + player->perp_wall_dist * player->ray_dir_x;
		player->wall_hit -= floor(player->wall_hit);
		tex_x = (int)(player->wall_hit * texture->width);
	}
	while (player->y < player->draw_end)
	{
		tex_y = (player->y - player->draw_start) * texture->height / player->line_height;
		color = texture->data[tex_y * texture->width + tex_x];
		player->screen_data[player->y * WINDOW_WIDTH + player->x] = color;
		player->y++;
	}
}

void	ceiling_floor_color(t_player *player)
{
	player->y = 0;
	while (player->y < player->draw_start)
	{
		player->screen_data[player->y * WINDOW_WIDTH + player->x] = player->ceiling_color;
		player->y++;
	}
	player->y = player->draw_end;
	while (player->y < WINDOW_HEIGHT)
	{
		player->screen_data[player->y * WINDOW_WIDTH + player->x] = player->floor_color;
		player->y++;
	}
}

void	draw_3d_view(t_player *player)
{
	t_texture *texture;
	double angle_increment;

	set_img(player);
	angle_increment = FOV / WINDOW_WIDTH;
	player->x = 0;
	while (player->x < WINDOW_WIDTH)
	{
		ray_dir(angle_increment,player);
		ray_travel(player);
		wall_height(player);
		texture = set_texter(player, texture);
		draw_texture(player, texture);
		ceiling_floor_color(player);
		player->x++;
	}
	mlx_put_image_to_window(player->mlx, player->mlx_win, player->screen_img, 0, 0);
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
	int			i;

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
	if (player->mlx)
		free(player->mlx);
	exit(0);
}


int	key_press(int keycode, void *params)
{
	t_player	*player;
	int			i;

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

void	set_angle(t_player *player)
{
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
	return (r << 16 | g << 8 | b);
}

void get_player_position(t_player *player)
{
	int i, j;

	i = 0;
	player->ceiling_color = rgb_to_int(NULL, 255, 255, 255);
	player->floor_color = rgb_to_int(NULL, 255, 255, 0);
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


int	main(void)
{
	t_player player;
	int map_width, map_height;

	player.map = (char *[]){
		("11111111111111111"),
		("100000000000000001"), 
		("10000010000000001"),	
		("1000010000000000111"),
		("10000000010000000001"),
		("1111110011011111111"), 
		("1000000010000111"), 
		("100001N1011111011111111"),
		("10000100000000001"), 
		("1000P00011111111"),
		("10000100000000001"), 
		("1000000100000001"),
		("10000100000000001"),
		("10000110000000001"),
		("11111111111111111"), 
		NULL};
	get_player_position(&player);
	set_angle(&player);
	player.mlx = mlx_init();
	if(player.mlx == NULL)
	{
		printf("Error\n");
		garbage_collector();
		exit(1);
	}
	player.mlx_win = mlx_new_window(player.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cude_3D");
	if(player.mlx_win == NULL)
	{
		printf("Error\n");
		garbage_collector();
		exit(1);
	}
	load_textures(&player);
	draw_3d_view(&player);
	mlx_hook(player.mlx_win, 2, 1L << 0, key_press, &player);
	mlx_hook(player.mlx_win, 17, 0, close_window, &player);
	mlx_loop(player.mlx);

	return (0);
}
