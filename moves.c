/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:33:44 by ansoulai          #+#    #+#             */
/*   Updated: 2024/06/08 00:40:32 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dispaly_moves_exit(t_player *player)
{
	player->count_moves++;
	ft_printf("moves = %d", player->count_moves);
	ft_printf("\033[0;32m\nYou W0N\033[0m");
	close_window(player);
	exit(0);
}

void	move_right(t_player *player)
{
	int	j;

	player->i = -1;
	while (player->map[++player->i])
	{
		j = -1;
		while (player->map[player->i][++j])
		{
			if (player->map[player->i][j] == 'P' && player->map[player->i][j + 1] == 'E'
				&& player->c == 0)
				dispaly_moves_exit(player);
			if (player->map[player->i][j] == 'P' && player->map[player->i][j + 1] != 'E'
				&& player->map[player->i][j + 1] != '1')
			{
				if (player->map[player->i][j + 1] == 'C')
					player->c = player->c - 1;
				player->map[player->i][j] = '0';
				player->map[player->i][j + 1] = 'P';
				draw_map(player);
				player->count_moves++;
				ft_printf("%d\n", player->count_moves);
				return ;
			}
		}
	}
}

void	move_left(t_player *player)
{
	int	j;

	player->i = -1;
	while (player->map[++player->i])
	{
		j = -1;
		while (player->map[player->i][++j])
		{
			if (player->map[player->i][j] == 'P' && player->map[player->i][j - 1] == 'E'
				&& player->c == 0)
				dispaly_moves_exit(player);
			if (player->map[player->i][j] == 'P' && player->map[player->i][j - 1] != 'E'
				&& player->map[player->i][j - 1] != '1')
			{
				if (player->map[player->i][j - 1] == 'C')
					player->c = player->c - 1;
				player->map[player->i][j] = '0';
				player->map[player->i][j - 1] = 'P';
				draw_map(player);
				player->count_moves++;
				ft_printf("%d\n", player->count_moves);
				return ;
			}
		}
	}
}

void	move_down(t_player *player)
{
	int	j;

	player->i = -1;
	while (player->map[++player->i])
	{
		j = -1;
		while (player->map[player->i][++j])
		{
			if (player->map[player->i][j] == 'P' && player->map[player->i + 1][j] == 'E'
				&& player->c == 0)
				dispaly_moves_exit(player);
			if (player->map[player->i][j] == 'P' && player->map[player->i + 1][j] != 'E'
				&& player->map[player->i + 1][j] != '1')
			{
				if (player->map[player->i + 1][j] == 'C')
					player->c = player->c - 1;
				player->map[player->i][j] = '0';
				player->map[player->i + 1][j] = 'P';
				draw_map(player);
				player->count_moves++;
				ft_printf("%d\n", player->count_moves);
				return ;
			}
		}
	}
}

void	move_up(t_player *player)
{
	int	j;

	player->i = -1;
	while (player->map[++player->i])
	{
		j = -1;
		while (player->map[player->i][++j])
		{
			if (player->map[player->i][j] == 'P' && player->map[player->i - 1][j] == 'E'
				&& player->c == 0)
				dispaly_moves_exit(player);
			if (player->map[player->i][j] == 'P' && player->map[player->i - 1][j] != 'E'
				&& player->map[player->i - 1][j] != '1')
			{
				if (player->map[player->i - 1][j] == 'C')
					player->c = player->c - 1;
				player->map[player->i][j] = '0';
				player->map[player->i - 1][j] = 'P';
				draw_map(player);
				player->count_moves++;
				ft_printf("%d\n", player->count_moves);
				return ;
			}
		}
	}
}
