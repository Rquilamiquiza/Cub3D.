/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:17 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/19 19:37:20 by rquilami         ###   ########.fr       */
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

    if (side == 1)
        color = 0xAAAAAA; // parede Y (horizontal), mais escura
    else
        color = 0xFFFFFF; // parede X (vertical), mais clara

    while (y < drawEnd)
    {
        mlx_pixel_put(core->mlx, core->win, x, y, color);
        y++;
    }
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
        data->stepX = -1;
        data->sideDistX = (data->posX - data->tileX) * data->deltaDistX;
    }
    else
    {
        data->stepX = 1;
        data->sideDistX = (data->tileX + 1.0 - data->posX) * data->deltaDistX;
    }

    if (data->raydirY < 0)
    {
        data->stepY = -1;
        data->sideDistY = (data->posY - data->tileY) * data->deltaDistY;
    }
    else
    {
        data->stepY = 1;
        data->sideDistY = (data->tileY + 1.0 - data->posY) * data->deltaDistY;
    }
}

// Prepara os dados de cada raio antes de usar o DDA
void measure(t_data *data, int x)
{
    data->cameraX = 2.0 * x / (float)data->column_map - 1.0;
    data->raydirX = data->DirX + data->planX * data->cameraX;
    data->raydirY = data->DirY + data->planY * data->cameraX;

    data->tileX = (int)data->posX;
    data->tileY = (int)data->posY;

    deltaDist(data);
    sideDist(data);
}

// Calcula distância perpendicular até a parede e limites da linha vertical
void calculate_dist(t_core *core, int x, int side)
{
    double WallDist;
    int lineHeight;
    int drawStart;
    int drawEnd;

    if (side == 0)
        WallDist = (core->data.tileX - core->data.posX + (1 - core->data.stepX) / 2) / core->data.raydirX;
    else
        WallDist = (core->data.tileY - core->data.posY + (1 - core->data.stepY) / 2) / core->data.raydirY;
    lineHeight = (int)(HEIGHT / WallDist);
    drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0)
        drawStart = 0;
    drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;
    draw_vertical_line(core, x, drawStart, drawEnd, side);
}

// Loop principal de raycasting
void dda(float fov, t_data *data, t_core *core)
{
    int x = 0;

    data->planX = data->DirY * fov;
    data->planY = -data->DirX * fov;

    while (x < data->column_map)
    {
        int hit = 0;
        int side = 0;

        measure(data, x); // calcula posição, direção e steps

        // DDA: avança até encontrar uma parede
        while (hit == 0)
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
                hit = 1;
        }
        calculate_dist(core, x, side); // calcula distância e desenha a linha
        x++;
    }
}


void raycasting(t_core *core)
{
    float fov;
    
    fov = 66.0f;
    dda(fov, &core->data, core);
}


