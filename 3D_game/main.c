#include "../cub3d.h"

void draw_mini_map(t_player *player)
{
	if (!player || !player->map)
		return;

	int frame_thickness = 2;
	int view_radius = 5;  // How many tiles to show around player
	int tile_size = 8;    // Size of each map tile in pixels
	
	// Calculate map dimensions
	int map_height = 0;
	int map_width = 0;
	while (player->map[map_height])
	{
		int row_width = 0;
		while (player->map[map_height][row_width])
			row_width++;
		if (row_width > map_width)
			map_width = row_width;
		map_height++;
	}

	// Calculate viewport boundaries
	int player_map_x = (int)player->px;
	int player_map_y = (int)player->py;
	
	int start_x = player_map_x - view_radius;
	int end_x = player_map_x + view_radius;
	int start_y = player_map_y - view_radius;
	int end_y = player_map_y + view_radius;
	
	// Clamp boundaries to map edges
	if (start_x < 0) 
		start_x = 0;
	if (start_y < 0) 
		start_y = 0;
	if (end_x >= map_width) 
		end_x = map_width - 1;
	if (end_y >= map_height) 
		end_y = map_height - 1;

	// Calculate mini-map dimensions
	int mini_map_size = (2 * view_radius + 1) * tile_size;
	int total_size = mini_map_size + 2 * frame_thickness;
	
	// Position mini-map in top-left corner with small margin
	int map_start_x = 10;
	int map_start_y = 10;

	// Draw frame
	int y = 0;
	while (y < total_size)
	{
		int x = 0;
		while (x < total_size)
		{
			if (y < frame_thickness || y >= total_size - frame_thickness ||
				x < frame_thickness || x >= total_size - frame_thickness)
			{
				int pos = (y + map_start_y) * WINDOW_WIDTH + (x + map_start_x);
				if (pos >= 0 && pos < WINDOW_WIDTH * WINDOW_HEIGHT)
					player->screen_player[pos] = 0x000000;  // Black frame
			}
			x++;
		}
		y++;
	}

	// Draw viewport background
	y = frame_thickness;
	while (y < total_size - frame_thickness)
	{
		int x = frame_thickness;
		while (x < total_size - frame_thickness)
		{
			int pos = (y + map_start_y) * WINDOW_WIDTH + (x + map_start_x);
			if (pos >= 0 && pos < WINDOW_WIDTH * WINDOW_HEIGHT)
				player->screen_player[pos] = 0x444444;  // Dark gray background
			x++;
		}
		y++;
	}

	// Draw visible portion of map
	int map_y = start_y;
	while (map_y <= end_y)
	{
		int map_x = start_x;
		while (map_x <= end_x)
		{
			if (map_y >= 0 && map_y < map_height && map_x >= 0 && map_x < map_width)
			{
				int local_x = map_x - start_x;
				int local_y = map_y - start_y;
				
				int mini_map_x = map_start_x + (local_x * tile_size) + frame_thickness;
				int mini_map_y = map_start_y + (local_y * tile_size) + frame_thickness;
				
				int color;
				if (player->map[map_y][map_x] == '1')
					color = 0x000000;  // Wall color
				else
					color = 0xFFFFFF;  // Empty space color

				// Draw map tile
				int i = 0;
				while (i < tile_size)
				{
					int j = 0;
					while (j < tile_size)
					{
						int pos = (mini_map_y + j) * WINDOW_WIDTH + (mini_map_x + i);
						if (pos >= 0 && pos < WINDOW_WIDTH * WINDOW_HEIGHT &&
							mini_map_x + i >= 0 && mini_map_x + i < WINDOW_WIDTH &&
							mini_map_y + j >= 0 && mini_map_y + j < WINDOW_HEIGHT)
						{
							player->screen_player[pos] = color;
						}
						j++;
					}
					i++;
				}
			}
			map_x++;
		}
		map_y++;
	}

	// Draw player in center of viewport
	int center_x = map_start_x + ((view_radius) * tile_size) + frame_thickness;
	int center_y = map_start_y + ((view_radius) * tile_size) + frame_thickness;
	
	// Draw player as a cross or arrow to show direction
	double dir_x = cos(player->angle) * (tile_size / 2);
	double dir_y = sin(player->angle) * (tile_size / 2);
	
	// Draw player position marker
	int i = -2;
	while (i <= 2)
	{
		int j = -2;
		while (j <= 2)
		{
			int pos = (center_y + j) * WINDOW_WIDTH + (center_x + i);
			if (pos >= 0 && pos < WINDOW_WIDTH * WINDOW_HEIGHT)
				player->screen_player[pos] = 0xFF0000;  // Red player marker
			j++;
		}
		i++;
	}
	
	// Draw direction indicator
	int t = 0;
	while (t < tile_size / 2)
	{
		int dir_pos_x = center_x + (int)(dir_x * t / (tile_size / 2));
		int dir_pos_y = center_y + (int)(dir_y * t / (tile_size / 2));
		int pos = dir_pos_y * WINDOW_WIDTH + dir_pos_x;
		if (pos >= 0 && pos < WINDOW_WIDTH * WINDOW_HEIGHT)
			player->screen_player[pos] = 0xFF0000;  // Red direction line
		t++;
	}
}

// void draw_mini_map(t_player *player)
// {
//     int map_x, map_y;
//     int mini_map_x, mini_map_y;
//     int color;
//     int frame_thickness = 2; // Thickness of the frame
//     int map_width = player->map_width;
//     int map_height = player->map_height;
//     double scale_x = (double)(MINI_MAP_SIZE - 2 * frame_thickness) / map_width;
//     double scale_y = (double)(MINI_MAP_SIZE - 2 * frame_thickness) / map_height;
// 	double scale;

// 	if (scale_x < scale_y)
// 		scale = scale_x;
// 	else
// 		scale = scale_y;

//     // Draw outer frame
// 	int i = 0, j;
// 	while (i < MINI_MAP_SIZE + 2 * frame_thickness)
// 	{
// 		j = 0;
// 		while (j < MINI_MAP_SIZE + 2 * frame_thickness)
// 		{
// 			if (i < frame_thickness || i >= MINI_MAP_SIZE + frame_thickness ||
// 				j < frame_thickness || j >= MINI_MAP_SIZE + frame_thickness)
// 			{
// 				player->screen_player[j * WINDOW_WIDTH + i] = 0x000000; // Black color
// 			}
// 			j++;
// 		}
// 		i++;
// 	}

// 	// Draw the entire mini-map background
// 	i = frame_thickness;
// 	while (i < MINI_MAP_SIZE + frame_thickness)
// 	{
// 		int j = frame_thickness;
// 		while (j < MINI_MAP_SIZE + frame_thickness)
// 		{
// 			player->screen_player[j * WINDOW_WIDTH + i] = 0xAAAAAA; // Light gray color for the background
// 			j++;
// 		}
// 		i++;
// 	}

// 	// Draw the mini-map
// 	map_y = 0;
// 	while (player->map[map_y])
// 	{
// 		map_x = 0;
// 		while (player->map[map_y][map_x])
// 		{
// 			mini_map_x = (int)(map_x * scale) + 2 * frame_thickness;
// 			mini_map_y = (int)(map_y * scale) + 2 * frame_thickness;
// 			if (player->map[map_y][map_x] == '1')
// 				color = 0xFFFFFF; // Wall color
// 			else
// 				color = 0x000000; // Empty space color

// 			i = 0;
// 			while (i < (int)scale)
// 			{
// 				int j = 0;
// 				while (j < (int)scale)
// 				{
// 					if (mini_map_x + i < MINI_MAP_SIZE + 2 * frame_thickness &&
// 						mini_map_y + j < MINI_MAP_SIZE + 2 * frame_thickness)
// 					{
// 						player->screen_player[(mini_map_y + j) * WINDOW_WIDTH + (mini_map_x + i)] = color;
// 					}
// 					j++;
// 				}
// 				i++;
// 			}
// 			map_x++;
// 		}
// 		map_y++;
// 	}

// 	// Draw player position on the mini-map
// 	mini_map_x = (int)(player->px * scale) + 2 * frame_thickness;
// 	mini_map_y = (int)(player->py * scale) + 2 * frame_thickness;
// 	i = 0;
// 	while (i < (int)scale)
// 	{
// 		int j = 0;
// 		while (j < (int)scale)
// 		{
// 			if (mini_map_x + i < MINI_MAP_SIZE + 2 * frame_thickness &&
// 				mini_map_y + j < MINI_MAP_SIZE + 2 * frame_thickness)
// 			{
// 				player->screen_player[(mini_map_y + j) * WINDOW_WIDTH + (mini_map_x + i)] = 0xFF0000; // Player color
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	draw_3d_view(t_player *player)
{
	t_texture *texture;
	double angle_increment;

	set_img(player);
	angle_increment = FOV / WINDOW_WIDTH;
	player->x = 0;
	while (player->x < WINDOW_WIDTH)
	{
		ray_dir(angle_increment,player);
		ray_travel(player);
		wall_height(player);
		texture = set_texter(player);
		draw_texture(player, texture);
		ceiling_floor_color(player);
		player->x++;
	}
	mlx_put_image_to_window(player->mlx, player->mlx_win, player->screen_img, 0, 0);
	draw_mini_map(player);
}


int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && (s1[i] == s2[i]) && s1[i] != '\0')
	{
		i++;
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}

// int	main(void)
// {
// 	t_player player;
// 	int map_width, map_height;

// 	get_map(&player);
// 	get_player_position(&player);
// 	set_angle(&player);
// 	player.mlx = mlx_init();
// 	if(player.mlx == NULL)
// 	{
// 		printf("Error\n");
// 		garbage_collector();
// 		exit(1);
// 	}
// 	player.mlx_win = mlx_new_window(player.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
// 			"cude_3D");
// 	if(player.mlx_win == NULL)
// 	{
// 		printf("Error\n");
// 		garbage_collector();
// 		exit(1);
// 	}
// 	load_textures(&player);
// 	draw_3d_view(&player);
// 	mlx_hook(player.mlx_win, 2, 1L << 0, key_press, &player);
// 	mlx_hook(player.mlx_win, 17, 0, close_window, &player);
// 	mlx_loop(player.mlx);
// 	return (0);
// }
