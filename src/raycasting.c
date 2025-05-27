/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:17 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/27 21:04:24 by justinosoar      ###   ########.fr       */
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

unsigned int get_pixel_color(t_img *tex, int x, int y)
{
    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0xFF0000); // Cor de fallback (vermelho)

    int pixel_offset = y * (tex->line_height / 4) + x;
    return tex->addr[pixel_offset];
}
int load_texture(t_core *core, int tex_num, char *path)
{
    t_img *tex = &core->imgs[tex_num];

    tex->img = mlx_xpm_file_to_image(core->mlx, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Error: Could not load texture %s\n", path);
        return (0);
    }

    // Note que estamos convertendo o retorno para int*
    tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp,
                                         &tex->line_height, &tex->endian);
    return (1);
}

void draw_vertical_line(t_core *core, int x, int drawStart, int drawEnd, int side)
{
    double wallX;
    int texX;
    double step;
    double texPos;
    int texY;
    int color;
    t_img *tex;

    // Selecionar textura correta
    if (side == 0)
    {
        tex = (core->data.raydirX > 0) ? &core->imgs[3] : &core->imgs[2]; // Oeste(3) ou Leste(2)
    }
    else
    {
        tex = (core->data.raydirY > 0) ? &core->imgs[1] : &core->imgs[0]; // Sul(1) ou Norte(0)
    }

    // Calcular posição exata na parede
    if (side == 0)
    {
        wallX = core->data.posY + core->data.perpWallDist * core->data.raydirY;
    }
    else
    {
        wallX = core->data.posX + core->data.perpWallDist * core->data.raydirX;
    }
    wallX -= floor(wallX);

    // Coordenada X da textura
    texX = (int)(wallX * (double)tex->width);

    // Inverter textura se necessário
    if ((side == 0 && core->data.raydirX > 0) || (side == 1 && core->data.raydirY < 0))
    {
        texX = tex->width - texX - 1;
    }

    // Calcular passo e posição inicial da textura
    step = (double)tex->height / (drawEnd - drawStart);
    texPos = (drawStart - HEIGHT / 2 + (drawEnd - drawStart) / 2) * step;

    // Desenhar a linha vertical com textura
    for (int y = drawStart; y < drawEnd; y++)
    {
        texY = (int)texPos;
        if (texY >= tex->height)
            texY = tex->height - 1; // Limitar ao tamanho da textura
        texPos += step;
        color = get_pixel_color(tex, texX, texY);
        put_pixel(core, x, y, color);
    }
}

void draw_wall(t_core *core, int x, int side)
{
    double lineHeight;
    int drawStart;
    int drawEnd;

    // Calcular distância perpendicular (já deve estar calculado no raycasting)
    if (side == 0)
    {
        core->data.perpWallDist = (core->data.tileX - core->data.posX + (1 - core->data.stepX) / 2) / core->data.raydirX;
    }
    else
    {
        core->data.perpWallDist = (core->data.tileY - core->data.posY + (1 - core->data.stepY) / 2) / core->data.raydirY;
    }

    // Calcular altura da linha
    lineHeight = (int)(HEIGHT / core->data.perpWallDist);

    // Calcular pontos de desenho
    drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0)
        drawStart = 0;

    drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;

    // Armazenar informações para uso posterior
    core->data.draw_start = drawStart;
    core->data.draw_end = drawEnd;
    core->data.line_height = lineHeight;
    core->data.side = side;

    // Desenhar a parede
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
