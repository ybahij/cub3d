/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:33:20 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/06 03:36:02 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_2d(t_player *player)
{
	if (!player->lines)
		exit_w_message("Error\n Invalid map\n");
	player->map = ft_malloc((player->height + 1) * sizeof(char *));
	if (!player->map)
		exit_w_message("Error\n Allocation failed\n");
	player->map = ft_split(player->lines, '\n');
	check_pce(player);
}

void	fill_map(t_player *player)
{
	int	i;
	int	j;

	player->max_width = 0;
	i = 0;
	while (player->map[i])
	{
		if ((int)ft_strlen(player->map[i]) > player->max_width)
			player->max_width = ft_strlen(player->map[i]);
		i++;
	}
	i = 0;
	while (player->map[i])
	{
		j = ft_strlen(player->map[i]);
		while (j < player->max_width)
		{
			player->map[i] = ft_strjoin(player->map[i], "1");
			j++;
		}
		player->map[i][j] = '\0';
		i++;
	}
}

void	starter(char *av, t_player *player)
{
	check_path(av);
	reading_map(av, player);
	// check_pce(player);
	map_2d(player);
	check_walls(player);
	fill_map(player);
}

void	map_height(t_player *player)
{
	int	i;

	i = 0;
	while (player->map[i])
		i++;
	player->height = i;
	player->width = 0;
	i = 0;
	while (player->map[i])
	{
		if ((int)ft_strlen(player->map[i]) > player->width)
			player->width = ft_strlen(player->map[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_player	player;

	if (ac != 2)
		exit_w_message("Takes two arguments\n");
	starter(av[1], &player);
	get_player_position(&player);
	set_angle(&player);
	player.mlx = mlx_init();
	if (player.mlx == NULL)
	{
		printf("Error\n");
		garbage_collector();
		exit(1);
	}
	ft_add_garbage(player.mlx);
	load_textures(&player);
	mlx_(&player);
	return (0);
}
