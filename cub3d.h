/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:33:30 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/02 11:25:54 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <mlx.h>
# include <math.h>
#include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	char			*line;
	struct s_node	*next;
}					t_node;

typedef struct s_minimap
{
	int	frame_thickness;
	int	view_radius;
	int	tile_size;
	int	map_height;
	int	map_width;
	int	player_map_x;
	int	player_map_y;
	int	viewport_size;
	int	start_x;
	int	end_x;
	int	start_y;
	int	end_y;
	int	mini_map_size;
	int	total_size;
	int	map_start_x;
	int	map_start_y;
	int	y;
	int	x;
	int	pos;
	int	map_y;
	int	map_x;
	int	local_x;
	int	local_y;
	int	mini_map_x;
	int	mini_map_y;
	int	color;
	int	i;
	int	j;
	int	relative_player_x;
	int	relative_player_y;
	int	player_screen_x;
	int	player_screen_y;
}	t_minimap;

typedef struct s_texture
{
	char		*path;
	void		*img;
	int			*player;
	int			width;
	int			height;
}				t_texture;
typedef struct s_player
{
	void			*mlx;
	void			*mlx_win;
	float		px;
	float		py;
	float		dir_x;
	float		dir_y;
	void			*player;
	void			*floor;
	void			*collectibles;
	void			*walls;
	void			*exit;
	void			*wall;
	char			**map;
	char			*tmp;
	char			*line;
	char			*lines;
	int				count_moves;
	int				height;
	int				width;
	char			**path[5];
	int				i;

	int				j;
	int				n;
	int				e;
	int				w;
	int				s;
	int				r;
	int 			ceiling_color;
	int				floor_color;
	int				*color_f;
	int				*color_c;
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
	t_minimap	*mm;
	void *screen_img;
	int			*screen_player;
}					t_player;
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define END "\033[0m"
# define RED "\033[0;31m"
# define NC "\033[0;0m"
# define W 119
# define D 100
# define S 115
# define A 97
# define ESC 65307

#define MOVE_SPEED 0.2
#define ROTATE_SPEED 0.2
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define MAP_SIZE 100
#define MINI_MAP_SCALE 10
#define MINI_MAP_SIZE 200
#define PI 3.14159265358979323846
#define FOV 60 * (PI / 180)

typedef struct s_garbage
{
	void	*ptr;
	struct s_garbage	*next;
}  t_garbage;

//=======================================================================================//

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *archive, char *buff);
char	*ft_new_archive(char *archive);
char	*ft_get_line(char *archive);
char	*ft_read_to_archive(int fd, char *archive);
char	*ft_strdup(char *src);

//=======================================================================================//

t_garbage **ft_garbage(void);
void	*ft_malloc(size_t size);
void	*ft_memset(void *b, int c, size_t len);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
char				*ft_substr(char *src, int start, int end);
void				exit_w_message(char *message);
size_t				ft_strlen_w_nl(char *str);
void				map_2d(t_player *player);
void				check_path(char *av);
void				check_pce(t_player *player);
char				*ft_strstr(char *str, char *to_find);
void				check_walls(t_player *player);
void				draw_map(t_player *player);
int					handler(int key, t_player *player);
void				message_xpm(t_player *player);
void				initialize_mlx_vars(t_player *player);
int					close_window_1(t_player *player);
void				add_line_to_list(t_node **head, char *line);
void				print_linked_list(t_node *head);
int					validate_color_string(char *path);
int					process_color_values(char *path, t_player *player, char color);
int					check_color_validity(char *path, t_player *player, char color);
int					initialize_direction_paths_for_color(t_player *player);
int					parse_nodes_colors(t_node *head, t_player *player);
char				**ft_split(char const *s, char c);
int					ft_atoi(char *str);
int					ft_isdigit(int c);
int					initialize_direction_paths(t_player *player);
int					check_path_validity(char *path);
int					parse_nodes_directions(t_node *head, t_player *player);
void				reading_map(char *av, t_player *player);
void				loop_map(t_player *player, int fd);
void				init_map_player(t_player *player);
void				check_path_with_access(char *path);
int					is_valid_direction(char *line);
int					process_direction_node(char *line, t_player *player, int index);
//=======================================================================================//

void garbage_collector(void);
void ft_add_garbage(void *ptr);
void	load_textures(t_player *player);
void	set_img(t_player *player);
void	draw_texture(t_player *player, t_texture *texture);
t_texture	*set_texter(t_player *player);
void load_texter(t_texture *texture, t_player *player, char *path);
void	set_angle(t_player *player);
int rgb_to_int(int *color, int r, int g, int b);
void get_player_position(t_player *player);
void get_map(t_player *player);
void	rotate_player(t_player *player, float angle);
void	destroy_img(t_texture *texture, t_player *player);
int	close_window(void *params);
int	key_press(int keycode, void *params);
void	move_player(t_player *player, float dx, float dy);
void	draw_texture(t_player *player, t_texture *texture);
void	ray_dist(t_player *player);
void	ray_dir(double  angle_increment,t_player *player);
void	ray_travel(t_player *player);
void	wall_height(t_player *player);
void	ceiling_floor_color(t_player *player);
void	draw_3d_view(t_player *player);
void draw_mini_map(t_player *player);
void	draw_3d_view(t_player *player);
void	mini_map_set(t_minimap *mm, t_player *p);
void	mini_map_u1(t_player *p);
void	min_map_u8(t_player *p);
void	mini_map_u2(t_player *p);
void	mini_map_u3(t_player *p);
void	mini_map_u4(t_player *p);
void	mini_map_u5(t_player *p);
void	mini_map_u6(t_player *p);
void	mini_map_u7(t_player *p);
void	mini_map_u8(t_player *p);

#endif