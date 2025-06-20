/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:10:25 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/20 19:37:22 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

void	delta_dist(t_data *data)
{
	if (data->raydir_x == 0)
		data->delta_dist_x = 1e30;
	else
		data->delta_dist_x = fabs(1.0 / data->raydir_x);
	if (data->raydir_y == 0)
		data->delta_dist_y = 1e30;
	else
		data->delta_dist_y = fabs(1.0 / data->raydir_y);
}

void	side_dist(t_data *data)
{
	if (data->raydir_x < 0)
	{
		data->side_dist_x = (data->pos_x - data->tile_x) * data->delta_dist_x;
		data->step_x = -1;
	}
	else
	{
		data->side_dist_x = (data->tile_x + 1.0 - data->pos_x)
			* data->delta_dist_x;
		data->step_x = 1;
	}
	if (data->raydir_y < 0)
	{
		data->side_dist_y = (data->pos_y - data->tile_y) * data->delta_dist_y;
		data->step_y = -1;
	}
	else
	{
		data->side_dist_y = (data->tile_y + 1.0 - data->pos_y)
			* data->delta_dist_y;
		data->step_y = 1;
	}
}

void	requirements(t_data *data, int x)
{
	data->camera_x = 2.0 * x / (double)WIDTH - 1.0;
	data->raydir_x = data->dir_x + data->plan_x * data->camera_x;
	data->raydir_y = data->dir_y + data->plan_y * data->camera_x;
	data->tile_x = (int)data->pos_x;
	data->tile_y = (int)data->pos_y;
	delta_dist(data);
	side_dist(data);
}

int	get_side(t_data *data, int wall, int side)
{
	while (!wall)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x;
			data->tile_x += data->step_x;
			side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->tile_y += data->step_y;
			side = 1;
		}
		if (data->tile_x < 0 || data->tile_y < 0
			|| data->tile_x >= data->column_map
			|| data->tile_y >= data->lines_map)
			break ;
		if (data->map_main[data->tile_y][data->tile_x] == '1')
			wall = 1;
	}
	return (side);
}

void	dda(double fov, t_data *data, t_core *core)
{
	int	x;
	int	side;
	int	wall;

	x = 0;
	(void)fov;
	while (x < WIDTH)
	{
		side = 0;
		wall = 0;
		requirements(data, x);
		side = get_side(data, wall, side);
		draw_wall(core, x, side);
		x++;
	}
}
