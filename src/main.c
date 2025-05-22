/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:46 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/22 14:10:34 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

void    init_config(t_core *core)
{
    core->mlx = mlx_init();
    core->win = mlx_new_window(core->mlx, WIDTH, HEIGHT, "cub3d");
    core->img = mlx_new_image(core->mlx, WIDTH, HEIGHT);
    core->addr = mlx_get_data_addr(core->img, &core->bpp, &core->line_size, &core->endian);
}

int press(int key, t_core *core)
{
    if (key == 65307)
        close_window(core);
    else if (key == 119)
        core->move.up = 1;
    else if (key == 115)
        core->move.down = 1;
    else if (key == 100)
        core->move.right = 1;
    else if (key == 97)
        core->move.left = 1;
    else if (key == 65361)
        core->move.rotation_l = 1;
    else if (key == 65363)
        core->move.rotation_r = 1;
    return (0);
}

int release(int key, t_core *core)
{
    if (key == 119)
        core->move.up = 0;
    else if (key == 115)
        core->move.down = 0;
    else if (key == 100)
        core->move.right = 0;
    else if (key == 97)
        core->move.left = 0;
    else if (key == 65361)
        core->move.rotation_l = 0;
    else if (key == 65363)
        core->move.rotation_r = 0;
    return (0);
}

void    moviments(t_core *core)
{
    if(core->move.up)
        core->data.posY -= MOVE_SPEED;
    if(core->move.down)
        core->data.posY += MOVE_SPEED;
    if(core->move.left)
        core->data.posX -= MOVE_SPEED;
    if(core->move.right)
        core->data.posX += MOVE_SPEED;
    if (core->move.rotation_l)
        core->data.initAngle -= ROT_SPEED;
    if (core->move.rotation_r)
        core->data.initAngle += ROT_SPEED;   
}

int main_loop(t_core *core)
{
    moviments(core);
    print_window(core);
    raycasting(core);
    mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);
    return (0);
}

void initVars(t_core *core)
{
    core->move.up = 0;
    core->move.down = 0;
    core->move.right = 0;
    core->move.left = 0;
    core->move.rotation_l = 0;
    core->move.rotation_r = 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return -1;
    t_core *core = calloc(1, sizeof(t_core));

    ft_readmap(argv[1], &core->data);
    initVars(core);
    init_config(core);

    mlx_hook(core->win, 17, 0, close_window, &core);
	mlx_hook(core->win, 2, 1L << 0, press, core);
	mlx_hook(core->win, 3, 1L << 1, release, core);
    mlx_loop_hook(core->mlx, main_loop, core);
    mlx_loop(core->mlx);
    return (0);
}
