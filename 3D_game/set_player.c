#include "../includes/cub3d.h"

void	set_angle(t_player *player)
{
	if (player->start_angle == 'N')
		player->angle = 0;
	else if (player->start_angle == 'E')
		player->angle = PI / 2;
	else if (player->start_angle == 'S')
		player->angle = PI;
	else if (player->start_angle == 'W')
		player->angle = 3 * PI / 2;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);

}

int rgb_to_int(int *color, int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void get_player_position(t_player *player)
{
	int i, j;

	i = 0;
	player->ceiling_color = rgb_to_int(NULL, 255, 255, 255);
	player->floor_color = rgb_to_int(NULL, 255, 255, 0);
	while (player->map[i])
	{
		j = 0;
		while (player->map[i][j])
		{
			if (player->map[i][j] == 'W' || player->map[i][j] == 'N'
				|| player->map[i][j] == 'E' || player->map[i][j] == 'S')
			{
				player->start_angle = player->map[i][j];
				player->px = j + 0.5;
				player->py = i + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

int ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(const char *s)
{
	char *str;
	int i;

	i = 0;
	str = ft_malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void get_map(t_player *player)
{
    int i = 0;
    int max_width = 0;
    char **map;

    map = ft_malloc(sizeof(char *) * 16);
    map[i++] = ft_strdup("        1111111111111111111111111");
    map[i++] = ft_strdup("        1000000000110000000000001");
    map[i++] = ft_strdup("        1011000001110000000000001");
    map[i++] = ft_strdup("        1001000000000000000000001");
    map[i++] = ft_strdup("111111111011000001110000000000001");
    map[i++] = ft_strdup("100000000011000001110111111111111");
    map[i++] = ft_strdup("11110111111111011100000010001");
    map[i++] = ft_strdup("11110111111111011101010010001");
    map[i++] = ft_strdup("11000000110101011100000010001");
    map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
	map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
    map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
    map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
	map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
    map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
	map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
    map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
    map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
	map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
    map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
	map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
    map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
    map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
	map[i++] = ft_strdup("10000000000000001100000010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
    map[i++] = ft_strdup("10000000000000001101010010001");
    map[i++] = ft_strdup("11000001110101011111011110N0111");
    map[i++] = ft_strdup("11110111 1110101 101111010001");
    map[i++] = ft_strdup("11111111 1111111 111111111111");
    map[i] = NULL;

    i = 0;
    while (map[i])
    {
        int line_length = strlen(map[i]);
        if (line_length > max_width)
        {
            max_width = line_length;
        }
        i++;
    }

    player->map = map;
    player->map_width = max_width;
    player->map_height = i;
}
