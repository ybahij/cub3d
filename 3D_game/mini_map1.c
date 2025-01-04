/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:21:23 by ybahij            #+#    #+#             */
/*   Updated: 2025/01/04 23:40:07 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
			p->mm->pos = (p->mm->mini_map_y + p->mm->j) * WINDOW_WIDTH
				+ (p->mm->mini_map_x + p->mm->i);
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

void	mini_map_u4(t_player *p)
{
	while (p->mm->map_y <= p->mm->end_y)
	{
		p->mm->map_x = p->mm->start_x;
		while (p->mm->map_x <= p->mm->end_x)
		{
			if (p->mm->map_y >= 0 && p->mm->map_y < p->mm->map_height
				&& p->mm->map_x >= 0 && p->mm->map_x < p->mm->map_width)
			{
				mini_map_u5(p);
				mini_map_u6(p);
			}
			p->mm->map_x++;
		}
		p->mm->map_y++;
	}
}

void	mini_map_u7(t_player *p)
{
	p->mm->relative_player_x = p->mm->player_map_x - p->mm->start_x;
	p->mm->relative_player_y = p->mm->player_map_y - p->mm->start_y;
	p->mm->player_screen_x = p->mm->map_start_x + (p->mm->relative_player_x
			* p->mm->tile_size) + p->mm->frame_thickness + (p->mm->tile_size
			/ 2);
	p->mm->player_screen_y = p->mm->map_start_y + (p->mm->relative_player_y
			* p->mm->tile_size) + p->mm->frame_thickness + (p->mm->tile_size
			/ 2);
}
