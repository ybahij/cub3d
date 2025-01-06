/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:10:24 by ansoulai          #+#    #+#             */
/*   Updated: 2025/01/05 02:09:32 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	exit_w_message(char *message)
{
	write(2, RED, ft_strlen(RED));
	write(2, message, ft_strlen(message));
	write(2, NC, ft_strlen(NC));
	garbage_collector();
	exit(1);
}

char	*ft_substr(char *src, int start, int end)
{
	int		i;
	char	*new_str;

	if (!src)
		return (NULL);
	i = 0;
	new_str = (char *)ft_malloc((end - start + 1) * sizeof(char));
	while (start < end)
	{
		new_str[i] = src[start];
		i++;
		start++;
	}
	new_str[i] = '\0';
	return (new_str);
}

size_t	ft_strlen_w_nl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (!str && to_find)
		return (0);
	if (to_find[0] == '\0' || to_find == str)
		return ((char *)str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == to_find[j])
		{
			if (str[i + j] == '\0' && to_find[j] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		if (to_find[j] == '\0' && str[i + j] == '\0')
			return ((char *)(str + i));
		i++;
	}
	return (0);
}
