/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:33:58 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/02 11:45:16 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	xpm_supor(t_player *player)
// {
// 	mlx_destroy_window(player->mlx, player->mlx_win);
// 	mlx_destroy_display(player->mlx);
// 	free(player->mlx);
// 	free_map(player);
// 	exit_w_message("Error, Invalid xpm");
// }

// void	message_xpm2(t_player *player)
// {
// 	if (!player->exit)
// 	{
// 		mlx_destroy_image(player->mlx, player->player);
// 		mlx_destroy_image(player->mlx, player->collectibles);
// 		mlx_destroy_image(player->mlx, player->wall);
// 		mlx_destroy_image(player->mlx, player->floor);
// 		xpm_supor(player);
// 	}
// 	if (!player->collectibles)
// 	{
// 		mlx_destroy_image(player->mlx, player->player);
// 		mlx_destroy_image(player->mlx, player->wall);
// 		mlx_destroy_image(player->mlx, player->floor);
// 		mlx_destroy_image(player->mlx, player->exit);
// 		xpm_supor(player);
// 	}
// 	if (!player->floor)
// 	{
// 		mlx_destroy_image(player->mlx, player->player);
// 		mlx_destroy_image(player->mlx, player->collectibles);
// 		mlx_destroy_image(player->mlx, player->wall);
// 		mlx_destroy_image(player->mlx, player->exit);
// 		xpm_supor(player);
// 	}
// }

// void	message_xpm(t_player *player)
// {
// 	message_xpm2(player);
// 	if (!player->player)
// 	{
// 		mlx_destroy_image(player->mlx, player->collectibles);
// 		mlx_destroy_image(player->mlx, player->wall);
// 		mlx_destroy_image(player->mlx, player->floor);
// 		mlx_destroy_image(player->mlx, player->exit);
// 		xpm_supor(player);
// 	}
// 	if (!player->wall)
// 	{
// 		mlx_destroy_image(player->mlx, player->player);
// 		mlx_destroy_image(player->mlx, player->collectibles);
// 		mlx_destroy_image(player->mlx, player->floor);
// 		mlx_destroy_image(player->mlx, player->exit);
// 		xpm_supor(player);
// 	}
// }

// void	initialize_mlx_vars(t_player *player)
// {
// 	player->count_moves = 0;
// 	player->mlx_win = mlx_new_window(player->mlx, player->width * 32, player->height
// 			* 32, "cub_3d");
// 	player->player = mlx_xpm_file_to_image(player->mlx,
// 			"textures/player.xpm",
// 			&player->width,
// 			&player->height);
// 	player->collectibles = mlx_xpm_file_to_image(player->mlx,
// 			"textures/collect.xpm",
// 			&player->width,
// 			&player->height);
// 	player->exit = mlx_xpm_file_to_image(player->mlx, "textures/exit.xpm",
// 			&player->width, &player->height);
// 	player->wall = mlx_xpm_file_to_image(player->mlx, "textures/wall.xpm",
// 			&player->width, &player->height);
// 	player->floor = mlx_xpm_file_to_image(player->mlx, "textures/floor.xpm",
// 			&player->width, &player->height);
// }
