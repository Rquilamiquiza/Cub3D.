/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:17 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/03 16:20:03 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

unsigned int	get_pixel_color(t_img *tex, int x, int y)
{
	int	pixel_offset;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0xFF0000);
	pixel_offset = y * (tex->line_height / 4) + x;
	return (tex->addr[pixel_offset]);
}

void	raycasting(t_core *core)
{
	double	fov;

	fov = 0.66;
	core->data.dir_x = cos(core->data.init_angle * PI / 180.0);
	core->data.dir_y = sin(core->data.init_angle * PI / 180.0);
	core->data.plan_x = core->data.dir_y * fov;
	core->data.plan_y = -core->data.dir_x * fov;
	dda(fov, &core->data, core);
}
