/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:17 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/01 17:35:18 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

unsigned int get_pixel_color(t_img *tex, int x, int y)
{
    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0xFF0000);

    int pixel_offset = y * (tex->line_height / 4) + x;
    return tex->addr[pixel_offset];
}


void raycasting(t_core *core)
{
    double fov;

    fov = 0.66;
    core->data.DirX = cos(core->data.initAngle * PI / 180.0);
    core->data.DirY = sin(core->data.initAngle * PI / 180.0);
    core->data.planX = core->data.DirY * fov;
    core->data.planY = -core->data.DirX * fov;
    dda(fov, &core->data, core);
}
