/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:46:58 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/06 01:06:48 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	validate_color_string(char *path)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	len = 0;
	while (path[len] && path[len] != '\n')
		len++;
	if (path[len] == '\n')
		path[len] = '\0';
	while (path[i] != '\0')
	{
		if (path[i] == ',')
			count++;
		else if (ft_isdigit(path[i]) == 0)
			return (1);
		i++;
	}
	if (count != 2)
		return (1);
	return (0);
}

int	process_color_values(char *path, t_player *player, char color)
{
	char	**split;
	int		number;
	int		*rgb;
	int		i;

	(void)player;
	rgb = ft_malloc(3 * sizeof(int));
	if (!path)
		exit_w_message("Error\n Invalid path\n");
	split = ft_split(path, ',');
	i = 0;
	while (split && i < 3)
	{
		number = ft_atoi(split[i]);
		if (number < 0 || number > 255)
			return (1);
		rgb[i] = number;
		i++;
	}
	if (color == 'F')
		player->color_f = rgb;
	else
		player->color_c = rgb;
	return (0);
}

int	check_color_validity(char *path, t_player *player, char color)
{
	if (validate_color_string(path))
	{
		printf("Error\n Invalid Color Structure\n");
		return (1);
	}
	return (process_color_values(path, player, color));
}
