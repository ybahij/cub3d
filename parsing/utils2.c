/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:19:33 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/05 02:26:18 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long int	result;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	trim_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
	{
		str[len - 1] = '\0';
	}
}

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

void	mlx_(t_player *player)
{
	player->mlx_win = mlx_new_window(player->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cude_3D");
	if (player->mlx_win == NULL)
	{
		printf("Error\n");
		garbage_collector();
		exit(1);
	}
	map_height(player);
	draw_3d_view(player);
	mlx_hook(player->mlx_win, 2, 1L << 0, key_press, player);
	mlx_hook(player->mlx_win, 17, 0, close_window, player);
	mlx_loop(player->mlx);
}
