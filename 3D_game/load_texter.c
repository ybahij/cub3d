#include "../cub3d.h"

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
	texture->player = (int *)mlx_get_data_addr(texture->img, &bpp,
			&size_line, &endian);

}

t_texture	*set_texter(t_player *player)
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

void	load_textures(t_player *player)
{
	player->north_texture = NULL;
	player->south_texture = NULL;
	player->west_texture = NULL;
	player->east_texture = NULL;
	player->screen_img = NULL;
	player->screen_player = NULL;
	player->north_texture = ft_malloc(sizeof(t_texture));
	load_texter(player->north_texture, player, "textures/north.xpm");
	player->south_texture = ft_malloc(sizeof(t_texture));
	load_texter(player->south_texture, player, "textures/south.xpm");
	player->west_texture  = ft_malloc(sizeof(t_texture));
	load_texter(player->west_texture, player, "textures/west.xpm");
	player->east_texture  = ft_malloc(sizeof(t_texture));
	load_texter(player->east_texture, player, "textures/east.xpm");
}

void	set_img(t_player *player)
{
	static void			*img = NULL;
	static int			*img_player = NULL;
	int bpp, size_line, endian;

	if (!img)
	{
		img = mlx_new_image(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		img_player = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	}
	player->screen_img = img;
	player->screen_player = img_player;
	ft_memset(img_player, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));
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
		color = texture->player[tex_y * texture->width + tex_x];
		player->screen_player[player->y * WINDOW_WIDTH + player->x] = color;
		player->y++;
	}
}