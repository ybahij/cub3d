#include "./includes/cub3d.h"

void draw_mini_map(t_player *player)
{
    int map_x, map_y;
    int mini_map_x, mini_map_y;
    int color;
    int frame_thickness = 2; // Thickness of the frame
    int map_width = player->map_width;
    int map_height = player->map_height;
    double scale_x = (double)(MINI_MAP_SIZE - 2 * frame_thickness) / map_width;
    double scale_y = (double)(MINI_MAP_SIZE - 2 * frame_thickness) / map_height;
    double scale = (scale_x < scale_y) ? scale_x : scale_y;

    // Draw outer frame
    for (int i = 0; i < MINI_MAP_SIZE + 2 * frame_thickness; i++)
    {
        for (int j = 0; j < MINI_MAP_SIZE + 2 * frame_thickness; j++)
        {
            if (i < frame_thickness || i >= MINI_MAP_SIZE + frame_thickness ||
                j < frame_thickness || j >= MINI_MAP_SIZE + frame_thickness)
            {
                player->screen_data[j * WINDOW_WIDTH + i] = 0x000000; // Black color
            }
        }
    }

    // Draw inner frame
    for (int i = frame_thickness; i < MINI_MAP_SIZE + frame_thickness; i++)
    {
        for (int j = frame_thickness; j < MINI_MAP_SIZE + frame_thickness; j++)
        {
            if (i < 2 * frame_thickness || i >= MINI_MAP_SIZE ||
                j < 2 * frame_thickness || j >= MINI_MAP_SIZE)
            {
                player->screen_data[j * WINDOW_WIDTH + i] = 0x000000; // Black color
            }
        }
    }

    // Draw the mini-map
    for (map_y = 0; player->map[map_y]; map_y++)
    {
        for (map_x = 0; player->map[map_y][map_x]; map_x++)
        {
            mini_map_x = (int)(map_x * scale) + 2 * frame_thickness;
            mini_map_y = (int)(map_y * scale) + 2 * frame_thickness;
            if (player->map[map_y][map_x] == '1')
                color = 0xFFFFFF; // Wall color
            else
                color = 0x000000; // Empty space color

            for (int i = 0; i < (int)scale; i++)
            {
                for (int j = 0; j < (int)scale; j++)
                {
                    if (mini_map_x + i < MINI_MAP_SIZE + 2 * frame_thickness &&
                        mini_map_y + j < MINI_MAP_SIZE + 2 * frame_thickness)
                    {
                        player->screen_data[(mini_map_y + j) * WINDOW_WIDTH + (mini_map_x + i)] = color;
                    }
                }
            }
        }
    }

    // Draw player position on the mini-map
    mini_map_x = (int)(player->px * scale) + 2 * frame_thickness;
    mini_map_y = (int)(player->py * scale) + 2 * frame_thickness;
    for (int i = 0; i < (int)scale; i++)
    {
        for (int j = 0; j < (int)scale; j++)
        {
            if (mini_map_x + i < MINI_MAP_SIZE + 2 * frame_thickness &&
                mini_map_y + j < MINI_MAP_SIZE + 2 * frame_thickness)
            {
                player->screen_data[(mini_map_y + j) * WINDOW_WIDTH + (mini_map_x + i)] = 0xFF0000; // Player color
            }
        }
    }
}

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
		texture = set_texter(player, texture);
		draw_texture(player, texture);
		ceiling_floor_color(player);
		player->x++;
	}
	draw_mini_map(player);
	mlx_put_image_to_window(player->mlx, player->mlx_win, player->screen_img, 0, 0);
}

int	main(void)
{
	t_player player;
	int map_width, map_height;

	get_map(&player);
	get_player_position(&player);
	set_angle(&player);
	player.mlx = mlx_init();
	if(player.mlx == NULL)
	{
		printf("Error\n");
		garbage_collector();
		exit(1);
	}
	player.mlx_win = mlx_new_window(player.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cude_3D");
	if(player.mlx_win == NULL)
	{
		printf("Error\n");
		garbage_collector();
		exit(1);
	}
	load_textures(&player);
	draw_3d_view(&player);
	mlx_hook(player.mlx_win, 2, 1L << 0, key_press, &player);
	mlx_hook(player.mlx_win, 17, 0, close_window, &player);
	mlx_loop(player.mlx);

	return (0);
}
