/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:36:05 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/22 13:59:27 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"



int close_window(t_core *core)
{
    (void)core;
    //mlx_destroy_window(core->mlx, core->win);
    //mlx_destroy_image(core->mlx, core->img);
    //mlx_destroy_display(core->mlx);
    //free_mtx(core->data.map);
    exit(0);
    return (0);
}

void clear_image(t_core *core, int color)
{
    int x, y;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            put_pixel(core, x, y, color);
        }
    }
}

void update_screen(t_core *core)
{
    //clear_image(core, 0xFFFFFF);
    print_window(core);
    raycasting(core);
    mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);
}


