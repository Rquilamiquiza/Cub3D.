/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:10:25 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/01 17:42:33 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

void deltaDist(t_data *data)
{
    if (data->raydirX == 0)
        data->deltaDistX = 1e30;
    else
        data->deltaDistX = fabs(1.0 / data->raydirX);

    if (data->raydirY == 0)
        data->deltaDistY = 1e30;
    else
        data->deltaDistY = fabs(1.0 / data->raydirY);
}

void sideDist(t_data *data)
{
    if (data->raydirX < 0)
    {
        data->sideDistX = (data->posX - data->tileX) * data->deltaDistX;
        data->stepX = -1;
    }
    else
    {
        data->sideDistX = (data->tileX + 1.0 - data->posX) * data->deltaDistX;
        data->stepX = 1;
    }

    if (data->raydirY < 0)
    {
        data->sideDistY = (data->posY - data->tileY) * data->deltaDistY;
        data->stepY = -1;
    }
    else
    {
        data->sideDistY = (data->tileY + 1.0 - data->posY) * data->deltaDistY;
        data->stepY = 1;
    }
}

void requirements(t_data *data, int x)
{
    data->cameraX = 2.0 * x / (double)WIDTH - 1.0;
    data->raydirX = data->DirX + data->planX * data->cameraX;
    data->raydirY = data->DirY + data->planY * data->cameraX;

    data->tileX = (int)data->posX;
    data->tileY = (int)data->posY;

    deltaDist(data);
    sideDist(data);
}

int get_side(t_data *data, int wall, int side)
{
    while (wall == 0)
    {
        if (data->sideDistX < data->sideDistY)
        {
            data->sideDistX += data->deltaDistX;
            data->tileX += data->stepX;
            side = 0;
        }
        else
        {
            data->sideDistY += data->deltaDistY;
            data->tileY += data->stepY;
            side = 1;
        }
        if (data->map_main[data->tileY][data->tileX] == '1')
            wall = 1;
    }
    return(side);
}

void dda(double fov, t_data *data, t_core *core)
{
    int x;
    int wall;
    int side;

    x = 0;
    (void)fov;
    while (x < WIDTH)
    {
        wall = 0;
        side = 0;
        requirements(data, x);
        side = get_side(data, wall, side);
        draw_wall(core, x, side);
        x++;
    }
}
