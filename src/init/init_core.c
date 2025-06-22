/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:31:50 by jsoares           #+#    #+#             */
/*   Updated: 2025/06/21 23:45:15 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

void init_core(t_core *core)
{
	core->mlx = NULL;
	core->win = NULL;
	core->win_height = HEIGHT;
	core->win_width = WIDTH;
	init_texinfo(&core->texinfo);
}

void init_texinfo(t_texinfo *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = 0;
	textures->ceiling = 0;
	textures->hex_floor = 0x0;
	textures->hex_ceiling = 0x0;
	textures->size = TEX_SIZE;
	textures->step = 0.0;
	textures->pos = 0.0;
	textures->x = 0;
	textures->y = 0;
}

void init_vars(t_core *core)
{
	core->move.up = 0;
	core->move.down = 0;
	core->move.right = 0;
	core->move.left = 0;
	core->move.rotation_l = 0;
	core->move.rotation_r = 0;
}

void init_config(t_core *core)
{
	core->mlx = mlx_init();
	if (!core->mlx)
		exit_error("Error trying open the windows", core);
	core->win = mlx_new_window(core->mlx, WIDTH, HEIGHT, "cub3d");
	core->img = mlx_new_image(core->mlx, WIDTH, HEIGHT);
	core->addr = mlx_get_data_addr(core->img, &core->bpp, &core->line_size,
								   &core->endian);
}
