/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:25:07 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/02 11:28:40 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	is_valid_direction(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

int	process_direction_node(char *line, t_player *player, int index)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!check_path_validity(split[1]))
		exit_w_message("Error\n Invalid path\n");
	if (split[1][2] == '.')
		exit_w_message("Error\n Invalid path\n");
	//access not allowed, but mlx_file_to_image can do the job
	player->path[index] = split;
	return (0);
}
