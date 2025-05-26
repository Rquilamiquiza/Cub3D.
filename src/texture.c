/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:25:59 by jsoares           #+#    #+#             */
/*   Updated: 2025/05/26 12:22:43 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

void init_texture_pixels(t_core *core)
{
    int i;

    if (core->texture_pixels)
        free_tab((void **)core->texture_pixels);
    core->texture_pixels = ft_calloc(core->win_height + 1,
                                     sizeof *core->texture_pixels);
    if (!core->texture_pixels)
        return;
    i = 0;
    while (i < core->win_height)
    {
        core->texture_pixels[i] = ft_calloc(core->win_width + 1,
                                            sizeof *core->texture_pixels);
        if (!core->texture_pixels[i])
            return;
        i++;
    }
}

static void get_texture_index(t_core *core, t_data *data)
{
    if (data->side == 0)
    {
        if (data->DirX < 0)
            core->texinfo.index = WEST;
        else
            core->texinfo.index = EAST;
    }
    else
    {
        if (data->DirY > 0)
            core->texinfo.index = SOUTH;
        else
            core->texinfo.index = NORTH;
    }
}

void update_texture_pixels(t_core *core, t_texinfo *tex, int x)
{
    int y;
    int color;

    get_texture_index(core, &core->data);
    tex->x = (int)(core->data.WallDist * tex->size);
    if ((core->data.side == 0 && core->data.DirX < 0) || (core->data.side == 1 && core->data.DirY > 0))
        tex->x = tex->size - tex->x - 1;
    tex->step = 1.0 * tex->size / core->data.wall_height;
    tex->pos = (core->data.draw_start - core->win_height / 2 
            + core->data.line_height / 2) * tex->step;
    y = core->data.draw_start;
    while (y < core->data.draw_end)
    {
        tex->y = (int)tex->pos & (tex->size - 1);
        tex->pos += tex->step;
        color = core->textures[tex->index][tex->size * tex->y + tex->x];
        if (tex->index == NORTH || tex->index == EAST)
            color = (color >> 1) & 8355711;
        if (color > 0)
            core->texture_pixels[y][x] = color;
        y++;
    }
}