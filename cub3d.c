/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:33:20 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/02 09:03:39 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
		ptr[i++] = (unsigned char)c;
	return (b);
}

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

void	starter(char *av, t_player *player)
{
	check_path(av);
	reading_map(av, player);
	map_2d(player);
	check_walls(player);
	map_2d(player);
}

void	map_height(t_player *player)
{
	int i;

	i = 0;
	while (player->map[i])
		i++;
	player->height = i;
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
	t_player player;

	if (ac != 2)
		exit_w_message("Takes two arguments\n");
	starter(av[1], &player);
	get_player_position(&player);
	set_angle(&player);
	player.mlx = mlx_init();
	if(player.mlx == NULL)
	{
		printf("Error\n");
		garbage_collector();
		exit(1);
	}
	ft_add_garbage(player.mlx);
	player.mlx_win = mlx_new_window(player.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cude_3D");
	if(player.mlx_win == NULL)
	{
		printf("Error\n");
		garbage_collector();
		exit(1);
	}
	load_textures(&player);
	draw_3d_view(&player);
	mlx_hook(player.mlx_win, 2, 1L << 0, key_press, &player);
	mlx_hook(player.mlx_win, 17, 0, close_window, &player);
	mlx_loop(player.mlx);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	t_player	player;

	// if (ac != 2)
	// 	exit_w_message("Takes two arguments\n");
// 	starter(av[1], &player);
// 	player.mlx = mlx_init();
// 	initialize_mlx_vars(&player);
// 	message_xpm(&player);
// 	// free_map(&player);
// 	reading_map(av[1], &player);
// 	map_2d(&player);
// 	// draw_map(&player);
// 	// mlx_hook(player.mlx_win, 2, 1L << 0, handler, &player);
// 	// mlx_hook(player.mlx_win, 17, 1L << 1, close_window_1, &player);
// 	// mlx_loop(player.mlx);
// 	// free_map(&player);
// 	return (0);
// }
