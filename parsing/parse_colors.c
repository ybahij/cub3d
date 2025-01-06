/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:23:29 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/06 05:22:58 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	initialize_direction_paths_for_color(t_player *player)
{
	int	i;

	i = 4;
	while (i < 6)
		player->path[i++] = NULL;
	return (0);
}

static int	is_valid_color_type(char *line)
{
	return (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2));
}

static int	check_duplicate_color(t_player *player, char *line,
		int current_index)
{
	int	j;

	j = 0;
	while (j < current_index)
	{
		if (player->path[j] && !ft_strncmp(line, player->path[j][0], 1))
			return (1);
		j++;
	}
	return (0);
}

static int	process_color_node(t_player *player, char *line, int index)
{
	char	**split;

	split = ft_split(line, ' ');
	if (check_color_validity(split[1], player, split[0][0]))
		exit_w_message("Error\n Invalid color number\n");
	player->path[index] = split;
	return (0);
}

int	parse_nodes_colors(t_node *head, t_player *player)
{
	t_node	*current;
	int		i;

	current = head;
	i = 4;
	initialize_direction_paths_for_color(player);
	while (current != NULL)
	{
		if (is_valid_color_type(current->line))
		{
			if (check_duplicate_color(player, current->line, i))
				return (1);
			if (process_color_node(player, current->line, i))
				return (1);
			i++;
		}
		current = current->next;
	}
	player->path[i] = NULL;
	return (0);
}
