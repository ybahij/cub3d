/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 01:23:43 by youssef           #+#    #+#             */
/*   Updated: 2024/10/07 19:32:31 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

#include "minilibx-linux/mlx.h"
#include <X11/X.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEG_TO_RAD(angle) ((angle) * M_PI / 180.0)

typedef struct s_player
{
    int px;
    int py;
    int x;
    int y;
    int dir;
    int turn_dir;
    int walk_dir;
    char **map;
    void *mlx;
    void *mlx_win;
    void *mlx_img;
    void *mlx_img2;
    int size;
    int colorwall;
    int coloropen;
} t_player;

void    draw_map(t_player *player);

#endif