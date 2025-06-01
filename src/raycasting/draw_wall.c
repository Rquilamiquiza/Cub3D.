/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:53:23 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/01 17:43:34 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

void draw_texture(t_core *core, t_img *tex, int texX, int x)
{
    double step;
    double texPos;
    int color;
    int texY;
    int y;

    step = (double)tex->height / (core->data.draw_end - core->data.draw_start);
    texPos = (core->data.draw_start - HEIGHT / 2 + (core->data.draw_end - core->data.draw_start) / 2) * step;
    y = core->data.draw_start;
    while (y < core->data.draw_end)
    {
        texY = (int)texPos;
        if (texY >= tex->height)
            texY = tex->height - 1; // Limitar ao tamanho da textura
        texPos += step;
        color = get_pixel_color(tex, texX, texY);
        put_pixel(core, x, y, color);
        y++;
    }
}

t_img *define_texture(t_core *core, int side)
{
    t_img *tex;

    if (side == 0)
    {
        if (core->data.raydirX > 0)
            tex = &core->imgs[3];
        else
            tex = &core->imgs[2];
    }
    else
    {
        if (core->data.raydirY > 0)
            tex = &core->imgs[1];
        else
            tex = &core->imgs[0]; // Sul(1) ou Norte(0)
    }
    return (tex);
}

void draw_vertical_line(t_core *core, int x, int side)
{
    double wallX;
    int texX;
    t_img *tex;

    tex = define_texture(core, side);
    if (side == 0)
        wallX = core->data.posY + core->data.perpWallDist * core->data.raydirY;
    else
        wallX = core->data.posX + core->data.perpWallDist * core->data.raydirX;
    wallX -= floor(wallX);
    texX = (int)(wallX * (double)tex->width);
    if ((side == 0 && core->data.raydirX > 0) || (side == 1 && core->data.raydirY < 0))
    {
        texX = tex->width - texX - 1;
    }
    draw_texture(core, tex, texX, x);
}

void draw_wall(t_core *core, int x, int side)
{
    double lineHeight;
    int drawStart;
    int drawEnd;

    if (side == 0)
        core->data.perpWallDist = (core->data.tileX - core->data.posX + (1 - core->data.stepX) / 2) / core->data.raydirX;
    else
        core->data.perpWallDist = (core->data.tileY - core->data.posY + (1 - core->data.stepY) / 2) / core->data.raydirY;
    lineHeight = (int)(HEIGHT / core->data.perpWallDist);
    drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0)
        drawStart = 0;
    drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;
    core->data.draw_start = drawStart;
    core->data.draw_end = drawEnd;
    core->data.line_height = lineHeight;
    core->data.side = side;
    draw_vertical_line(core, x, side);
}
