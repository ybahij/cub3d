/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 04:00:58 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/06 03:51:13 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//NORM == OK funct has 25 lines
static int	open_map_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_w_message("File not found!\n");
	return (fd);
}

static char	*skip_empty_lines(int fd, char *line)
{
	while (line && (line[0] == '\n' || line[0] == '\0'))
		line = get_next_line(fd);
	return (line);
}

static int	process_first_map_line(t_player *player, char *line)
{
	char	*temp;

	player->line = line;
	player->width = (int)ft_strlen_w_nl(player->line);
	if (!player->width)
		exit_w_message("ERROR\n Empty map!\n");
	if (player->line[(int)ft_strlen(player->line) - 1] == '\n')
	{
		player->width = (int)ft_strlen(player->line);
		temp = player->line;
		player->line = ft_substr(player->line, 0, player->width);
	}
	return (0);
}

static int	parse_map_header(t_node *head, t_player *player)
{
	if (parse_nodes_directions(head, player))
		exit_w_message("Error\n ctions\n");
	if(parse_nodes_colors(head, player))
		exit_w_message("Error\n Colors Structure \n");
	return (0);
}

void	reading_map(char *av, t_player *player)
{
	int		fd;
	char	*line;
	t_node	*head;
	int		lines_read;

	head = NULL;
	lines_read = 0;
	init_map_player(player);
	fd = open_map_file(av);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL || (ft_isdigit(line[0])
				|| line[0] == '1'))
			break ;
		if (line[0] != '\n' && line[0] != '\0')
		{
			add_line_to_list(&head, line);
			lines_read++;
		}
	}
	parse_map_header(head, player);
	skip_empty_lines(fd, line);
	process_first_map_line(player, line);
	loop_map(player, fd);
}
