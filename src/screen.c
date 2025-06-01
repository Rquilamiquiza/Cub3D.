/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:14:44 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/01 13:31:12 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

void put_pixel(t_core *core, int x, int y, int color)
{
    char *pixel;

    pixel = core->addr + (y * core->line_size + x * (core->bpp / 8));
    *(unsigned int *)pixel = color;
}

void init_color(t_core *core)
{
    char *word;

    word = first_word(core->data.map_color[0]);
    if (word[0] == 'C')
    {
        core->sky = convert_color(core->data.map_color[0]);
        core->floor = convert_color(core->data.map_color[1]);
    }
    else
    {
        core->sky = convert_color(core->data.map_color[1]);
        core->floor = convert_color(core->data.map_color[0]);
    }
    free(word);
}

void print_window(t_core *core)
{
    int x;
    int y;

    x = 0;
    y = 0;

    init_color(core);
    while (y < HEIGHT)
    {
        while (x < WIDTH)
        {
            if (y < HEIGHT / 2)
                core->color = core->sky;
            else
                core->color = core->floor;
            put_pixel(core, x, y, core->color);
            x++;
        }
        x = 0;
        y++;
    }
}
