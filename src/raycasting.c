/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:17 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/05 18:18:21 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

char map[HEIGHT][WIDTH] = {
    "111111111",
    "100N01101",
    "100000001",
    "100100001",
    "100000001",
    "111111111"
};

void draw_map(t_core *core)
{
    int x = 0;
    int y = 0;
    int i = 0;
    int j;
    while (y < MAP_HEIGHT)
    {   
        x = 0;
        while (x < MAP_WIDTH)
        {
            if (map[y][x] == '1')
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

int find_player(int *px, int *py)
{
    int y = 0;
    int x = 0;
    while (y < MAP_HEIGHT)
    {
        x = 0;
        while (x < MAP_WIDTH)
        {
            if (map[y][x] == 'N')
            {
                *px = x;
                *py = y;
                return 1;
            }
            x++;
        }
        y++;
    }
    return 0;
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
        if (px < 0 || px >= MAP_WIDTH || py < 0 || py >= MAP_HEIGHT)
            break;
        if (map[py][px] == '1')
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
    find_player(&px, &py);
    float angle;

    angle = initAngle - 30;
    while (angle <= initAngle + 30) 
    {
        dda(px, py, angle, core);
        angle += 0.1f;
    }
}

