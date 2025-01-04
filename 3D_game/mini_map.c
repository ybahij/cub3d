/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:20:36 by ybahij            #+#    #+#             */
/*   Updated: 2025/01/05 00:08:06 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	mm->mini_map_size = 0;
	mini_map_set1(mm);
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

void	min_map_u8(t_player *p)
{
	while (p->mm->x < p->mm->total_size)
	{
		if (p->mm->y < p->mm->frame_thickness
			|| p->mm->y >= p->mm->total_size - p->mm->frame_thickness
			|| p->mm->x < p->mm->frame_thickness
			|| p->mm->x >= p->mm->total_size - p->mm->frame_thickness)
		{
			p->mm->pos = (p->mm->y + p->mm->map_start_y) * WINDOW_WIDTH
				+ (p->mm->x + p->mm->map_start_x);
			if (p->mm->pos >= 0 && p->mm->pos < WINDOW_WIDTH
				* WINDOW_HEIGHT)
				p->screen_player[p->mm->pos] = 0x000000;
		}
		p->mm->x++;
	}
}

void	mini_map_u2(t_player *p)
{
	p->mm->mini_map_size = p->mm->viewport_size * p->mm->tile_size;
	p->mm->total_size = p->mm->mini_map_size + 2 * p->mm->frame_thickness;
	p->mm->map_start_x = 10;
	p->mm->map_start_y = 10;
	p->mm->y = 0;
	min_map_u8(p);
	p->mm->y = p->mm->frame_thickness;
}

void	mini_map_u3(t_player *p)
{
	while (p->mm->y < p->mm->total_size - p->mm->frame_thickness)
	{
		p->mm->x = p->mm->frame_thickness;
		while (p->mm->x < p->mm->total_size - p->mm->frame_thickness)
		{
			p->mm->pos = (p->mm->y + p->mm->map_start_y) * WINDOW_WIDTH
				+ (p->mm->x + p->mm->map_start_x);
			if (p->mm->pos >= 0 && p->mm->pos < WINDOW_WIDTH * WINDOW_HEIGHT)
				p->screen_player[p->mm->pos] = 0x444444;
			p->mm->x++;
		}
		p->mm->y++;
	}
	p->mm->map_y = p->mm->start_y;
}
