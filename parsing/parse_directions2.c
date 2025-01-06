/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:25:07 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/06 05:23:39 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	is_valid_direction(char *line)
{
	char	*tmp;

	tmp = skip_spaces(line);
	line = tmp;
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
	player->path[index] = split;
	return (0);
}

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}
