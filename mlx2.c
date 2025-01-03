/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:33:52 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/02 11:46:07 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	handler(int key, t_player *player)
// {
// 	if (key == ESC)
// 	{
// 		close_window(player);
// 		exit(0);
// 	}
// 	if (key == W)
// 		move_up(player);
// 	if (key == A)
// 		move_left(player);
// 	if (key == S)
// 		move_down(player);
// 	if (key == D)
// 		move_right(player);
// 	return (1);
// }


void	draw_map(t_player *player)
{
	mlx_clear_window(player->mlx, player->mlx_win);
	player->i = -1;
	while (player->map[++player->i])
	{
		player->j = -1;
		while (player->map[player->i][++player->j])
		{
			if (player->map[player->i][player->j] == 'P')
				mlx_put_image_to_window(player->mlx, player->mlx_win, player->player,
					player->j * 32, player->i * 32);
			if (player->map[player->i][player->j] == '0')
				mlx_put_image_to_window(player->mlx, player->mlx_win, player->floor,
					player->j * 32, player->i * 32);
			if (player->map[player->i][player->j] == 'C')
				mlx_put_image_to_window(player->mlx, player->mlx_win,
					player->collectibles, player->j * 32, player->i * 32);
			if (player->map[player->i][player->j] == '1')
				mlx_put_image_to_window(player->mlx, player->mlx_win, player->wall,
					player->j * 32, player->i * 32);
			if (player->map[player->i][player->j] == 'E')
				mlx_put_image_to_window(player->mlx, player->mlx_win, player->exit,
					player->j * 32, player->i * 32);
		}
	}
}
