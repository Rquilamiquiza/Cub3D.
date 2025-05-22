/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:17 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/22 15:33:21 by rquilami         ###   ########.fr       */
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


void draw_vertical_line(t_core *core, int x, int drawStart, int drawEnd, int side)
{
    int y = drawStart;
    int color;

    if (side == 0)
        color = 0xFFFFFF;
    else
        color = 0xFFFF00;
    while (y < drawEnd)
    {
        put_pixel(core, x, y, color);
        y++;
    }
}

// Calcula distância perpendicular até a parede e limites da linha vertical
void draw_wall(t_core *core, int x, int side)
{
    double WallDist;
    double lineHeight;
    int drawStart;
    int drawEnd;
    // o valor de HEIGHT é de 900

    (void)x;
    if (side == 0)
        WallDist = (core->data.tileX - core->data.posX + (1 - core->data.stepX) / 2) / core->data.raydirX;
    else
        WallDist = (core->data.tileY - core->data.posY + (1 - core->data.stepY) / 2) / core->data.raydirY;
    lineHeight = (int)(HEIGHT / WallDist);
    drawStart = (HEIGHT - lineHeight) / 2;
    if (drawStart < 0)
        drawStart = 0;
    drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;

    
    draw_vertical_line(core, x, drawStart, drawEnd, side);
}

// Calcula deltaDist para eixo X e Y
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

// Calcula step (direção) e sideDist (distância inicial até primeira borda de tile)
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

// Prepara os dados de cada raio antes de usar o DDA
void requirements(t_data *data, int x)
{
    data->cameraX = 2.0 * x / (float)WIDTH - 1.0;
    data->raydirX = data->DirX + data->planX * data->cameraX;
    data->raydirY = data->DirY + data->planY * data->cameraX;

    data->tileX = (int)data->posX;
    data->tileY = (int)data->posY;

    deltaDist(data);
    sideDist(data);
}

void dda(float fov, t_data *data, t_core *core)
{
    int x = 0;

    data->DirX = cos(data->initAngle * PI/180.0);
    data->DirY = sin(data->initAngle * PI/180.0);
    data->planX = data->DirY * fov;
    data->planY = -data->DirX * fov;
    while (x < WIDTH)
    {
        int wall = 0;
        int side = 0;

        requirements(data, x);
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
            if (data->map[data->tileY][data->tileX] == '1')
                wall = 1;
        }
        draw_wall(core, x, side);
        x++;
    }
}

void raycasting(t_core *core)
{
    float fov;
    
    fov = 0.66;
    dda(fov, &core->data, core);
}


