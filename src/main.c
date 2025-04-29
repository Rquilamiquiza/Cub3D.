/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:46 by rquilami          #+#    #+#             */
/*   Updated: 2025/04/29 19:23:47 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

void    init_config(core_t *core)
{
    core->mlx = mlx_init();
    core->win = mlx_new_window(core->mlx, WIDTH, HEIGTH, "cub3d");
    core->img = mlx_new_image(core->mlx, WIDTH, HEIGTH);
    core->addr = mlx_get_data_addr(core->img, &core->bpp, &core->line_size, &core->endian);
}

int main ()
{
    core_t *core;
    core = malloc(sizeof(core_t));

    init_config(core);
    print_window(core);
    mlx_loop(core->mlx);
    return (0);
}
