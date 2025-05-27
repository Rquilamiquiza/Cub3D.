/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:36:05 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/27 20:17:22 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

int isWall(float px, float py, t_core *core)
{
    int x;
    int y;

    x = px;
    y = py;
    if (core->data.map[y][x] == '1')
        return (1);
    return (0);
}

void upDown(t_core *core, float dirx, float diry)
{
    if (core->move.up)
    {
        core->move.newStepX = core->data.posX + dirx * MOVE_SPEED;
        core->move.newStepY = core->data.posY + diry * MOVE_SPEED;
        if (!isWall(core->move.newStepX, core->move.newStepY, core))
        {
            core->data.posX = core->move.newStepX;
            core->data.posY = core->move.newStepY;
        }
    }
    if (core->move.down)
    {
        core->move.newStepX = core->data.posX - dirx * MOVE_SPEED;
        core->move.newStepY = core->data.posY - diry * MOVE_SPEED;
        if (!isWall(core->move.newStepX, core->move.newStepY, core))
        {
            core->data.posX = core->move.newStepX;
            core->data.posY = core->move.newStepY;
        }
    }
}

void leftRight(t_core *core, float dirx, float diry)
{
    if (core->move.left)
    {
        core->move.newStepX = core->data.posX - diry * MOVE_SPEED;
        core->move.newStepY = core->data.posY + dirx * MOVE_SPEED;
        if (!isWall(core->move.newStepX, core->move.newStepY, core))
        {
            core->data.posX = core->move.newStepX;
            core->data.posY = core->move.newStepY;
        }
    }
    if (core->move.right)
    {
        core->move.newStepX = core->data.posX + diry * MOVE_SPEED;
        core->move.newStepY = core->data.posY - dirx * MOVE_SPEED;
        if (!isWall(core->move.newStepX, core->move.newStepY, core))
        {
            core->data.posX = core->move.newStepX;
            core->data.posY = core->move.newStepY;
        }
    }
}

void moviments(t_core *core)
{
    float dirx;
    float diry;

    if (core->move.rotation_l)
    {
        if (core->data.initAngle > 360.0)
            core->data.initAngle = 0.0;
        core->data.initAngle += ROT_SPEED;
    }
    if (core->move.rotation_r)
    {
        if (core->data.initAngle < 0.0)
            core->data.initAngle = 360.0;
        core->data.initAngle -= ROT_SPEED;
    }
    dirx = cos(core->data.initAngle * PI / 180.0);
    diry = sin(core->data.initAngle * PI / 180.0);
    upDown(core, dirx, diry);
    leftRight(core, dirx, diry);
}

int close_window(t_core *core)
{
    (void)core;
    // mlx_destroy_window(core->mlx, core->win);
    // mlx_destroy_image(core->mlx, core->img);
    // mlx_destroy_display(core->mlx);
    // free_mtx(core->data.map);
    exit(0);
    return (0);
}
