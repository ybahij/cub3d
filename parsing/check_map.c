/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:34:26 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/06 03:33:15 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_valid_check_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_surrounding_walls(t_player *player, int i, int j, int height)
{
	if (i == 0 || i == height - 1 || j == 0 || !player->map[i][j + 1]
		|| !player->map[i + 1] || !player->map[i - 1] || !player->map[i][j - 1])
		return (1);
	if (player->map[i][j + 1] == ' ' || player->map[i][j - 1] == ' '
		|| player->map[i + 1][j] == ' ' || player->map[i - 1][j] == ' ')
		return (1);
	if (player->map[i][j + 1] == '\0' || player->map[i][j - 1] == '\0'
		|| player->map[i + 1][j] == '\0' || player->map[i - 1][j] == '\0')
		return (1);
	return (0);
}

void	check_walls(t_player *player)
{
	int	i;
	int	j;
	int	height;

	i = 0;
	height = 0;
	while (player->map[height])
		height++;
	while (player->map[i])
	{
		j = 0;
		while (player->map[i][j])
		{
			if (is_valid_check_char(player->map[i][j]))
			{
				if (check_surrounding_walls(player, i, j, height))
				{
					exit_w_message("ERROR\n Invalid map\n");
				}
			}
			j++;
		}
		i++;
	}
}

void	check_path(char *av)
{
	char	*str;
	char	*to_find;
	size_t	len;
	int		i;

	to_find = ".cub";
	str = av;
	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1] == '/')
			exit_w_message("ERROR\n Invalid path\n");
		i++;
	}
	if (len <= 4)
		exit_w_message("ERROR\n Invalid path\n");
	if (((str[len - 5] == '/') || ft_strstr(str, to_find) == 0))
		exit_w_message("ERROR\n Invalid path\n");
}
