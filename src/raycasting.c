/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:17 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/07 16:04:32 by rquilami         ###   ########.fr       */
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


void dda(float x0, float y0, float angle, t_core *core)
{
    float angleRad = angle * PI / 180.0;
    float dx = cos(angleRad);
    float dy = sin(angleRad);
    
    float x = x0 + 0.5f;
    float y = y0 + 0.5f;
    
    while (1)
    {
        int px = (int)x;
        int py = (int)y;
        if (px < 0 || px >= core->data.column_map || py < 0 || py >= core->data.lines_map)
            break;
        if (core->data.map[py][px] == '1')
            break;
        int screenX = (int)(x * BLOCK);
        int screenY = (int)(y * BLOCK);
        put_pixel(core, screenX, screenY, 0x00FF0000);
        x += dx * 0.1f;
        y += dy * 0.1f;
    }

}

void vision_player(t_core *core, float initAngle)
{
    int px;
    int py;
    find_player(&px, &py, &core->data);
    float angle;

    angle = initAngle - 30;
    while (angle <= initAngle + 30) 
    {
        dda(px, py, angle, core);
        angle += 0.1f;
    }
}

