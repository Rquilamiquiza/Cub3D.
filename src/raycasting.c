/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:17 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/25 00:10:28 by jsoares          ###   ########.fr       */
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

int get_pixel_color(t_img *img, int x, int y)
{
    char *pixel;
    int color;

    pixel = img->addr + (y * img->line_height + x * (img->bpp / 8));
    color = *(unsigned int *)pixel;
    return color;
}

void draw_vertical_line(t_core *core, int x, int drawStart, int drawEnd, int side)
{
    int y = drawStart;
    double step;
    double texPos;
    int tex_x, tex_y;
    t_img *tex;

    // Escolher textura com base na direção do raio
    if (side == 0)
    {
        if (core->data.raydirX > 0)
            tex = &core->textures[0]; // parede norte
        else
            tex = &core->textures[1]; // parede sul
    }
    else
    {
        if (core->data.raydirY > 0)
            tex = &core->textures[2]; // parede leste
        else
            tex = &core->textures[3]; // parede oeste
    }

    // Calcular posição x na textura
    double wallX;
    if (side == 0)
        wallX = core->data.posY + core->data.perpWallDist * core->data.raydirY;
    else
        wallX = core->data.posX + core->data.perpWallDist * core->data.raydirX;
    wallX -= floor(wallX);

    tex_x = (int)(wallX * (double)tex->width);
    if ((side == 0 && core->data.raydirX < 0) || (side == 1 && core->data.raydirY > 0))
        tex_x = tex->width - tex_x - 1;

    // Definir passo e posição inicial na textura (eixo Y)
    step = 1.0 * tex->height / (drawEnd - drawStart);
    texPos = (drawStart - HEIGHT / 2 + (drawEnd - drawStart) / 2) * step;

    // Desenhar linha vertical com textura
    while (y < drawEnd)
    {
        tex_y = (int)texPos & (tex->height - 1); // para texturas com altura 2^n
        texPos += step;
        int color = get_pixel_color(tex, tex_x, tex_y);
        put_pixel(core, x, y, color);
        y++;
    }
}


void draw_wall(t_core *core, int x, int side)
{
    double WallDist;
    double lineHeight;
    int drawStart;
    int drawEnd;

    (void)x;
    if (side == 0)
        WallDist = (core->data.tileX - core->data.posX + (1 - core->data.stepX) / 2.0) / core->data.raydirX;
    else
        WallDist = (core->data.tileY - core->data.posY + (1 - core->data.stepY) / 2.0) / core->data.raydirY;

    lineHeight = HEIGHT / WallDist;
    if (lineHeight > HEIGHT)
        lineHeight = HEIGHT;
    drawStart = (int)((HEIGHT / 2.0) - (lineHeight / 2.0));
    drawEnd = (int)((HEIGHT / 2.0) + (lineHeight / 2.0));
    draw_vertical_line(core, x, drawStart, drawEnd, side);
}

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

void dda(double fov, t_data *data, t_core *core)
{
    int x = 0;

    data->DirX = cos(data->initAngle * PI / 180.0);
    data->DirY = sin(data->initAngle * PI / 180.0);
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
    double fov;

    fov = 0.66;
    dda(fov, &core->data, core);
}
