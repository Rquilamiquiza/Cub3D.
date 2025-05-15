/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:46 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/13 08:51:17 by rquilami         ###   ########.fr       */
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

int main(int argc, char *argv[])
{
    if (argc != 2)
        return -1;
    t_core *core = calloc(1, sizeof(t_core));

    init_config(core);
    ft_readmap(argv[1], &core->data);
    print_window(core);
    draw_map(core);
    vision_player(core, 0);
    mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);

    mlx_hook(core->win, 17, 0, close_window, &core);
	mlx_hook(core->win, 2, 1L << 0, keyCall, &core);
    mlx_loop(core->mlx);
    return (0);
}
