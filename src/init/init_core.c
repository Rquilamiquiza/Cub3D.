/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:31:50 by jsoares           #+#    #+#             */
/*   Updated: 2025/06/01 13:37:31 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

void	init_core(t_core *core)
{
	core->mlx = NULL;
	core->win = NULL;
	core->win_height = HEIGHT;
	core->win_width = WIDTH;
	init_texinfo(&core->texinfo);
	core->texture_pixels = NULL;
	core->textures = NULL;
}

void	init_texinfo(t_texinfo *textures)
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

void init_data(t_core *core)
{
	core->data.cameraX = 0;	
	core->data.cameraY = 0;	
	core->data.stepX = 0;	
	core->data.stepY = 0;	
	core->data.playerx = 0;	
	core->data.playery = 0;	
	core->data.tileX = 0;	
	core->data.tileY = 0;	
	core->data.lines_map = 0;	
	core->data.column_map = 0;	
	core->data.raydirX = 0.0;	
	core->data.raydirY =  0.0;	
	core->data.sideDistX =  0.0;	
	core->data.sideDistY =  0.0;	
	core->data.DirX =  0.0;
	core->data.DirY =  0.0;
	core->data.posX =  0.0;
	core->data.posY =  0.0;	
	core->data.planX =  0.0;	
	core->data.planY =  0.0;	
	core->data.fov = 0.66;	
	core->data.WallDist = 0.0;	
	core->data.side = 0;	
	core->data.line_height = 0;	
	core->data.draw_start = 0;	
	core->data.draw_end = 0;	
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

void init_config(t_core *core)
{
    core->mlx = mlx_init();
    core->win = mlx_new_window(core->mlx, WIDTH, HEIGHT, "cub3d");
    core->img = mlx_new_image(core->mlx, WIDTH, HEIGHT);
    core->addr = mlx_get_data_addr(core->img, &core->bpp, &core->line_size, &core->endian);
}


