/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:36:05 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/07 16:45:01 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

int close_window(t_core *core)
{
    (void)core;
    //mlx_destroy_window(core->mlx, core->win);
    //mlx_destroy_image(core->mlx, core->img);
    //mlx_destroy_display(core->mlx);
    //free_mtx(core->data.map);
    exit(0);
    return (0);
}

int keyCall(int key, t_core *core)
{
    if (key == 65307)
        close_window(core);
    if (key == 119)
        printf("clicou em w\n");
    if (key == 115)
        printf("clicou em s\n");
    if (key == 100)
        printf("clicou em d\n");
    if (key == 97)
        printf("clicou em a\n");
    if (key == 65361)
        printf("clicou em <\n");
    if (key == 65363)
        printf("clicou em >\n");
    
    return (0);
}
