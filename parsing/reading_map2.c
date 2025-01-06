/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 04:18:55 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/06 05:30:22 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//NORM == OK
void	loop_map(t_player *player, int fd)
{
	char	*line;

	while (player->line != NULL)
	{
		player->height++;
		if (player->line[(int)ft_strlen(player->line) - 1] == '\n')
		{
			player->width = (int)ft_strlen(player->line);
			line = player->line;
			player->line = ft_substr(player->line, 0, player->width);
		}
		player->lines = ft_strjoin(player->lines, player->line);
		player->line = get_next_line(fd);
	}
	close(fd);
}

void	add_line_to_list(t_node **head, char *line)
{
	t_node	*new_node;
	t_node	*temp;

	new_node = ft_malloc(sizeof(t_node));
	if (!new_node)
		exit_w_message("Memory allocation failed!\n");
	new_node->line = ft_strdup(line);
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	init_map_player(t_player *player, char *av)
{
	player->lines = NULL;
	player->height = 0;
	player->lines_read = 0;
	player->fd_map = open_map_file(av);
}

void	print_linked_list(t_node *head)
{
	t_node	*temp;

	temp = head;
	while (temp)
	{
		printf("%s\n", temp->line);
		temp = temp->next;
	}
}
