#include "../cub3d.h"

void	mini_map_set(t_minimap *mm, t_player *p)
{
	mm->frame_thickness = 2;
	mm->view_radius = 5;
	mm->tile_size = 8;
	mm->map_height = p->height;
	mm->map_width = p->width;
	mm->player_map_x = (int)p->px;
	mm->player_map_y = (int)p->py;
	mm->viewport_size = 2 * mm->view_radius + 1;
	mm->start_x = mm->player_map_x - mm->view_radius;
	mm->end_x = mm->start_x + mm->viewport_size - 1;
	mm->start_y = mm->player_map_y - mm->view_radius;
	mm->end_y = mm->start_y + mm->viewport_size - 1;
}

void	mini_map_u1(t_player *p)
{
	if (p->mm->start_x < 0)
	{
		p->mm->start_x = 0;
		p->mm->end_x = p->mm->viewport_size - 1;
	}
	else if (p->mm->end_x >= p->mm->map_width)
	{
		p->mm->end_x = p->mm->map_width - 1;
		p->mm->start_x = p->mm->end_x - p->mm->viewport_size + 1;
	}
	if (p->mm->start_y < 0)
	{
		p->mm->start_y = 0;
		p->mm->end_y = p->mm->viewport_size - 1;
	}
	else if (p->mm->end_y >= p->mm->map_height)
	{
		p->mm->end_y = p->mm->map_height - 1;
		p->mm->start_y = p->mm->end_y - p->mm->viewport_size + 1;
	}
}

void mini_map_u2(t_player *p)
{
	p->mm->mini_map_size = p->mm->viewport_size * p->mm->tile_size;
	p->mm->total_size = p->mm->mini_map_size + 2 * p->mm->frame_thickness;
	p->mm->map_start_x = 10;
	p->mm->map_start_y = 10;
	p->mm->y = 0;
	while (p->mm->y < p->mm->total_size)
	{
		p->mm->x = 0;
		while (p->mm->x < p->mm->total_size)
		{
			if (p->mm->y < p->mm->frame_thickness || p->mm->y >= p->mm->total_size - p->mm->frame_thickness
				|| p->mm->x < p->mm->frame_thickness || p->mm->x >= p->mm->total_size - p->mm->frame_thickness)
			{
				p->mm->pos = (p->mm->y + p->mm->map_start_y) * WINDOW_WIDTH + (p->mm->x + p->mm->map_start_x);
				if (p->mm->pos >= 0 && p->mm->pos < WINDOW_WIDTH * WINDOW_HEIGHT)
					p->screen_player[p->mm->pos] = 0x000000;
			}
			p->mm->x++;
		}
		p->mm->y++;
	}
	p->mm->y = p->mm->frame_thickness;
}

void	mini_map_u3(t_player *p)
{
	while (p->mm->y < p->mm->total_size - p->mm->frame_thickness)
	{
		p->mm->x = p->mm->frame_thickness;
		while (p->mm->x < p->mm->total_size - p->mm->frame_thickness)
		{
			p->mm->pos = (p->mm->y + p->mm->map_start_y) * WINDOW_WIDTH + (p->mm->x + p->mm->map_start_x);
			if (p->mm->pos >= 0 && p->mm->pos < WINDOW_WIDTH * WINDOW_HEIGHT)
				p->screen_player[p->mm->pos] = 0x444444;
			p->mm->x++;
		}
		p->mm->y++;
	}
	p->mm->map_y = p->mm->start_y;
}

void	mini_map_u5(t_player *p)
{
	p->mm->local_x = p->mm->map_x - p->mm->start_x;
	p->mm->local_y = p->mm->map_y - p->mm->start_y;
	p->mm->mini_map_x = p->mm->map_start_x + (p->mm->local_x * p->mm->tile_size)
		+ p->mm->frame_thickness;
	p->mm->mini_map_y = p->mm->map_start_y + (p->mm->local_y * p->mm->tile_size)
		+ p->mm->frame_thickness;
	if (p->map[p->mm->map_y][p->mm->map_x] == '1')
		p->mm->color = 0x000000;
	else
		p->mm->color = 0xFFFFFF;
	p->mm->i = 0;
}

void	mini_map_u6(t_player *p)
{
	while (p->mm->i < p->mm->tile_size)
	{
		p->mm->j = 0;
		while (p->mm->j < p->mm->tile_size)
		{
			p->mm->pos = (p->mm->mini_map_y + p->mm->j) * WINDOW_WIDTH + (p->mm->mini_map_x
					+ p->mm->i);
			if (p->mm->pos >= 0 && p->mm->pos < WINDOW_WIDTH * WINDOW_HEIGHT
				&& p->mm->mini_map_x + p->mm->i >= 0 && p->mm->mini_map_x
				+ p->mm->i < WINDOW_WIDTH && p->mm->mini_map_y + p->mm->j >= 0
				&& p->mm->mini_map_y + p->mm->j < WINDOW_HEIGHT)
			{
				p->screen_player[p->mm->pos] = p->mm->color;
			}
			p->mm->j++;
		}
		p->mm->i++;
	}
}

void mini_map_u4(t_player *p)
{
	while (p->mm->map_y <= p->mm->end_y)
	{
		p->mm->map_x = p->mm->start_x;
		while (p->mm->map_x <= p->mm->end_x)
		{
			if (p->mm->map_y >= 0 && p->mm->map_y < p->mm->map_height && p->mm->map_x >= 0
				&& p->mm->map_x < p->mm->map_width)
			{
				mini_map_u5(p);
				mini_map_u6(p);
			}
			p->mm->map_x++;
		}
		p->mm->map_y++;
	}
}

void	draw_mini_map(t_player *p)
{
	p->mm = ft_malloc(sizeof(t_minimap));
	mini_map_set(p->mm, p);
	mini_map_u1(p);
	mini_map_u2(p);
	mini_map_u3(p);
	mini_map_u4(p);
	p->mm->relative_player_x = p->mm->player_map_x - p->mm->start_x;
	p->mm->relative_player_y = p->mm->player_map_y - p->mm->start_y;
	p->mm->player_screen_x = p->mm->map_start_x + (p->mm->relative_player_x * p->mm->tile_size)
		+ p->mm->frame_thickness + (p->mm->tile_size / 2);
	p->mm->player_screen_y = p->mm->map_start_y + (p->mm->relative_player_y * p->mm->tile_size)
		+ p->mm->frame_thickness + (p->mm->tile_size / 2);
	p->mm->i = -3;
	while (p->mm->i <= 3)
	{
		p->mm->j = -3;
		while (p->mm->j <= 3)
		{
			p->mm->pos = (p->mm->player_screen_y + p->mm->j) * WINDOW_WIDTH + (p->mm->player_screen_x + p->mm->i);
			if (p->mm->pos >= 0 && p->mm->pos < WINDOW_WIDTH * WINDOW_HEIGHT)
				p->screen_player[p->mm->pos] = 0xFF0000;
			p->mm->j++;
		}
		p->mm->i++;
	}
}

void	draw_3d_view(t_player *player)
{
	t_texture	*texture;
	double		angle_increment;

	set_img(player);
	angle_increment = FOV / WINDOW_WIDTH;
	player->x = 0;
	while (player->x < WINDOW_WIDTH)
	{
		ray_dir(angle_increment, player);
		ray_travel(player);
		wall_height(player);
		texture = set_texter(player);
		draw_texture(player, texture);
		ceiling_floor_color(player);
		player->x++;
	}
	mlx_put_image_to_window(player->mlx, player->mlx_win, player->screen_img, 0,
		0);
	draw_mini_map(player);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && (s1[i] == s2[i]) && s1[i] != '\0')
	{
		i++;
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}
