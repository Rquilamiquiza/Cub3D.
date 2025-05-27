/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:46 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/27 20:58:59 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

void init_config(t_core *core)
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

int load_textures(t_core *core)
{
    if (!load_texture(core, 0, "images/black_bricks.xpm") ||
        !load_texture(core, 1, "images/blue_hole.xpm") ||
        !load_texture(core, 2, "images/sama.xpm") ||
        !load_texture(core, 3, "images/wall.xpm"))
    {
        printf("Error loading textures\n");
        return (0);
    }
    return (1);
}

int main_loop(t_core *core)
{
    init_texture_pixels(core);
    moviments(core);
    print_window(core);
    raycasting(core);
    //render_frame(core);
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
    init_core(core);

    ft_readmap(argv[1], &core->data);
    initVars(core);
    // init_data(core);
    init_config(core);
    load_textures(core);
    //init_texture(core);

    mlx_hook(core->win, 17, 0, close_window, &core);
    mlx_hook(core->win, 2, 1L << 0, press, core);
    mlx_hook(core->win, 3, 1L << 1, release, core);
    mlx_loop_hook(core->mlx, main_loop, core);
    mlx_loop(core->mlx);
    return (0);
}
