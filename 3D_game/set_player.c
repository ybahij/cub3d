/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:24:41 by ybahij            #+#    #+#             */
/*   Updated: 2025/01/04 23:25:21 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_texture(t_player *player, t_texture *texture)
{
	int	tex_x;
	int	tex_y;
	int	color;

	player->y = player->draw_start;
	texture_draw(player, texture, &tex_x);
	while (player->y < player->draw_end)
	{
		tex_y = (player->y - player->draw_start) * texture->height
			/ player->line_height;
		color = texture->player[tex_y * texture->width + tex_x];
		player->screen_player[player->y * WINDOW_WIDTH + player->x] = color;
		player->y++;
	}
}

void	mini_map_set1(t_minimap *mm)
{
	mm->total_size = 0;
	mm->map_start_x = 0;
	mm->map_start_y = 0;
	mm->x = 0;
	mm->y = 0;
	mm->pos = 0;
	mm->local_x = 0;
	mm->local_y = 0;
	mm->mini_map_x = 0;
	mm->mini_map_y = 0;
	mm->color = 0;
	mm->i = 0;
	mm->j = 0;
	mm->relative_player_x = 0;
	mm->relative_player_y = 0;
	mm->player_screen_x = 0;
	mm->player_screen_y = 0;
}

void	set_angle(t_player *player)
{
	player->mlx = NULL;
	player->mlx_win = NULL;
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

int	rgb_to_int(int *color, int r, int g, int b)
{
	(void)color;
	return (r << 16 | g << 8 | b);
}

void	get_player_position(t_player *player)
{
	int	i;
	int	j;

	i = 0;
	player->ceiling_color = rgb_to_int(NULL, player->color_c[0],
			player->color_c[1], player->color_c[2]);
	player->floor_color = rgb_to_int(NULL, player->color_f[0],
			player->color_f[1], player->color_f[2]);
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
