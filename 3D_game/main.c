#include "../cub3d.h"

void	draw_mini_map(t_player *p)
{
	p->mm = ft_malloc(sizeof(t_minimap));
	mini_map_set(p->mm, p);
	mini_map_u1(p);
	mini_map_u2(p);
	mini_map_u3(p);
	mini_map_u4(p);
	mini_map_u7(p);
    p->mm->i = -3;
    while (p->mm->i <= 3)
    {
        p->mm->j = -3;
        while (p->mm->j <= 3)
        {
            p->mm->pos = (p->mm->player_screen_y + p->mm->j) * WINDOW_WIDTH + (p->mm->player_screen_x + p->mm->i);
            if (p->mm->pos >= 0 && p->mm->pos < WINDOW_WIDTH * WINDOW_HEIGHT)
            {
                p->screen_player[p->mm->pos] = 0xFF0000;
            }
            p->mm->j++;
        }
        p->mm->i++;
    }
}

void	draw_3d_view(t_player *player)
{
	t_texture	*texture;
	double		angle_increment;

	set_img(player);
	angle_increment = FOV / WINDOW_WIDTH;
	player->x = 0;
	while (player->x < WINDOW_WIDTH)
	{
		ray_dir(angle_increment, player);
		ray_travel(player);
		wall_height(player);
		texture = set_texter(player);
		draw_texture(player, texture);
		ceiling_floor_color(player);
		player->x++;
	}
	mlx_put_image_to_window(player->mlx, player->mlx_win, player->screen_img, 0,
		0);
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
