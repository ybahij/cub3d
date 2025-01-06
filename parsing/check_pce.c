/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:24:24 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/06 05:21:31 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_error(t_player *player)
{
	if (player->n + player->e + player->w + player->s != 1 || player->r != 0)
		exit_w_message("ERROR\n The map should have N,E,W or S\n");
}

void	initialize_pce(t_player *player)
{
	if (!(player->map))
		exit_w_message("ERROR\n No map found\n");
	player->i = 0;
	player->n = 0;
	player->e = 0;
	player->w = 0;
	player->s = 0;
	player->r = 0;
}

void	check_pce(t_player *player)
{
	initialize_pce(player);
	while (player->map[player->i])
	{
		player->j = 0;
		while (player->map[player->i][player->j])
		{
			if (player->map[player->i][player->j] == 'N')
				player->n++;
			else if (player->map[player->i][player->j] == 'E')
				player->e++;
			else if (player->map[player->i][player->j] == 'W')
				player->w++;
			else if (player->map[player->i][player->j] == 'S')
				player->s++;
			else if ((player->map[player->i][player->j] != '1')
					&& (player->map[player->i][player->j] != '0')
					&& player->map[player->i][player->j] != ' ')
				player->r++;
			player->j++;
		}
		player->i++;
	}
	print_error(player);
}
