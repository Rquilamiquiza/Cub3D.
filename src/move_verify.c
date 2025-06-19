/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_verify.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:36:30 by jsoares           #+#    #+#             */
/*   Updated: 2025/06/19 13:40:35 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

float	direction(t_core *core, float value)
{
	if (core->data.side == 0)
	{
		if (core->data.raydir_x > 0)
			return (value + 0.25);
		else
			return (value - 0.25);
	}
	else
	{
		if (core->data.raydir_y > 0)
			return (value + 0.25);
		else
			return (value - 0.25);
	}
	return (value);
}

int	is_wall(float px, float py, t_core *core, int slide)
{
	int	x;
	int	y;

	if (slide == 0)
	{
		x = (int)direction(core, px);
		y = (int)direction(core, py);
	}
	if (slide == SLIDE_X)
	{
		x = (int)direction(core, px);
		y = (int)py;
	}
	if (slide == SLIDE_Y)
	{
		x = (int)px;
		y = (int)direction(core, py);
	}
	if (x < 0 || x >= core->data.column_map || y < 0
		|| y >= core->data.lines_map)
		return (1);
	if (core->data.map_main[y][x] == '1')
		return (1);
	return (0);
}
