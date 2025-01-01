/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 01:23:43 by youssef           #+#    #+#             */
/*   Updated: 2025/01/01 23:25:05 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

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
#define MINI_MAP_SCALE 10
#define MINI_MAP_SIZE 200
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

void	set_angle(t_player *player);
int rgb_to_int(int *color, int r, int g, int b);
void get_player_position(t_player *player);
char *ft_strdup(const char *s);
void get_map(t_player *player);
void	rotate_player(t_player *player, float angle);
void	destroy_img(t_texture *texture, t_player *player);
int	close_window(void *params);
int	key_press(int keycode, void *params);
void	move_player(t_player *player, float dx, float dy);
int        ft_strlen(const char *s);
t_texture	*set_texter(t_player *player, t_texture *texture);
void	draw_texture(t_player *player, t_texture *texture);
void	ray_dist(t_player *player);
void	ray_dir(double  angle_increment,t_player *player);
void	ray_travel(t_player *player);
void	wall_height(t_player *player);
void	ceiling_floor_color(t_player *player);

#endif