/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:20:34 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/06 03:20:56 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_path_validity(char *path)
{
	if (!path)
		return (1);
	if (!ft_strncmp(path, "./", 2))
		return (1);
	return (0);
}

int	initialize_direction_paths(t_player *player)
{
	int	i;

	i = 0;
	while (i < 4)
		player->path[i++] = NULL;
	return (0);
}

static int	check_duplicate_direction(t_player *player, char *line,
		int current_index)
{
	int	j;

	j = 0;
	while (j < current_index)
	{
		if (player->path[j] && !ft_strncmp(line, player->path[j][0], 2))
			return (1);
		j++;
	}
	return (0);
}
char *skip_spaces(char *str) 
{
	if(!str)
		return NULL;
    while (*str && (*str == ' ' || *str == '\t'))
        str++;
    return str;
}

static int	process_single_direction(t_player *player, t_node *current,
		int index)
{
	if (!is_valid_direction(current->line))
		exit_w_message("Error\n Invalid directions\n");
	if (check_duplicate_direction(player, current->line, index))
		return (1);
	if (process_direction_node(current->line, player, index))
		return (1);
	return (0);
}

int	parse_nodes_directions(t_node *head, t_player *player)
{
	t_node	*current;
	int		i;


	current = head;
	i = 0;
	initialize_direction_paths(player);
	while (current != NULL && i < 4)
	{
		if (process_single_direction(player, current, i))
			return (1);
		i++;
		current = current->next;
	}
	player->path[i] = NULL;
	return (0);
}
