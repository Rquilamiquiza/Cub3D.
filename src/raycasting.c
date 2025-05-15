/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:17 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/15 14:09:36 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"


void draw_map(t_core *core)
{
    int x = 0;
    int y = 0;
    int i = 0;
    int j;
    while (y < core->data.lines_map)
    {   
        x = 0;
        while (x < core->data.column_map)
        {
            if (core->data.map[y][x] == '1')
            {
                i = 0;
                while (i < BLOCK)
                {
                    j = 0;
                    while (j < BLOCK)
                    {
                        put_pixel(core, x * BLOCK + j, y * BLOCK + i, 0xFFFFFF);
                        j++;
                    }
                    i++;
                }
            }
            x++;
        }
        y++;
    }
}


void dda(float angle, float fov, t_data *data)
{   
    int px;
    int py;
    int x;
    int stepX, stepY;

    px = 0;
    py = 0;
    x = 0;

    data->planY = -data->DirY * fov;
    data->planX =  data->DirX * fov;

    px = (int)data->posX;
    py = (int)data->posY;

    while (x < data->column_map)
    {
        data->cameraX = 2.0 * x / data->column_map - 1.0;
        data->raydirY = data->DirY + data->planY * data->cameraX;
        data->raydirX = data->DirX + data->planX * data->cameraX;
        x++;

    }
    data->deltaDistX = abs(1/data->raydirX);
    data->deltaDistY = abs(1/data->raydirY);
    if (data->raydirX < 0)
    {
        stepX = -1;
        data->sideDistX = (data->posX - px) * data->deltaDistX;
    }
    else
    {
        stepX = 1;
        data->sideDistX = (px + 1.0 - data->posX) * data->deltaDistX;
    }

    if (data->raydirY < 0)
    {
        stepY = -1;
        data->sideDistY = (data->posY - py) * data->deltaDistY;
    }
    else
    {
        stepY = 1;
        data->sideDistY = (py + 1.0 - data->posY) * data->deltaDistY;
        py -= stepY;
    }


}

void vision_player(t_core *core, float initAngle)
{
    int px;
    int py;
    float fov;
    float angle;
    float step;
    
    find_player(&px, &py, &core->data);
    fov = 60.0f;
    step = 0.1f;
    angle = initAngle - (fov / 2.0f);

    while (angle <= initAngle + (fov / 2.0f)) 
    {
        dda(px, py, angle, core);
        angle += step;
    }
}


