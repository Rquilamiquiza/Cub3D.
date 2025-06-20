/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:36:05 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/20 19:22:00 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

int	is_wall(float px, float py, t_core *core)
{
	int	x;
	int	y;

	x = (int)px;
	y = (int)py;
	if (x < 0 || y < 0 || x >= core->data.column_map
		|| y >= core->data.lines_map)
		return (1);
	if (!core->data.map_main || !core->data.map_main[y])
		return (1);
	return (core->data.map_main[y][x] == '1');
}

void	up(t_core *core, float dir_x, float dir_y)
{
	float	next_x;
	float	next_y;

	next_x = core->data.pos_x + dir_x * MOVE_SPEED;
	next_y = core->data.pos_y + dir_y * MOVE_SPEED;
	if (!is_wall(next_x + PLAYER_RADIUS, core->data.pos_y, core)
		&& !is_wall(next_x - PLAYER_RADIUS, core->data.pos_y, core))
		core->data.pos_x = next_x;
	if (!is_wall(core->data.pos_x, next_y + PLAYER_RADIUS, core)
		&& !is_wall(core->data.pos_x, next_y - PLAYER_RADIUS, core))
		core->data.pos_y = next_y;
}

void	down(t_core *core, float dir_x, float dir_y)
{
	float	next_x;
	float	next_y;

	next_x = core->data.pos_x - dir_x * MOVE_SPEED;
	next_y = core->data.pos_y - dir_y * MOVE_SPEED;
	if (!is_wall(next_x + PLAYER_RADIUS, core->data.pos_y, core)
		&& !is_wall(next_x - PLAYER_RADIUS, core->data.pos_y, core))
		core->data.pos_x = next_x;
	if (!is_wall(core->data.pos_x, next_y + PLAYER_RADIUS, core)
		&& !is_wall(core->data.pos_x, next_y - PLAYER_RADIUS, core))
		core->data.pos_y = next_y;
}

void	left_right(t_core *core, float dir_x, float dir_y)
{
	if (core->move.left)
	{
		core->next_x = core->data.pos_x - dir_y * MOVE_SPEED;
		core->next_y = core->data.pos_y + dir_x * MOVE_SPEED;
		if (!is_wall(core->next_x + PLAYER_RADIUS, core->data.pos_y, core)
			&& !is_wall(core->next_x - PLAYER_RADIUS, core->data.pos_y, core))
			core->data.pos_x = core->next_x;
		if (!is_wall(core->data.pos_x, core->next_y + PLAYER_RADIUS, core)
			&& !is_wall(core->data.pos_x, core->next_y - PLAYER_RADIUS, core))
			core->data.pos_y = core->next_y;
	}
	if (core->move.right)
	{
		core->next_x = core->data.pos_x + dir_y * MOVE_SPEED;
		core->next_y = core->data.pos_y - dir_x * MOVE_SPEED;
		if (!is_wall(core->next_x + PLAYER_RADIUS, core->data.pos_y, core)
			&& !is_wall(core->next_x - PLAYER_RADIUS, core->data.pos_y, core))
			core->data.pos_x = core->next_x;
		if (!is_wall(core->data.pos_x, core->next_y + PLAYER_RADIUS, core)
			&& !is_wall(core->data.pos_x, core->next_y - PLAYER_RADIUS, core))
			core->data.pos_y = core->next_y;
	}
}

void	moviments(t_core *core)
{
	float	dir_x;
	float	dir_y;

	if (core->move.rotation_l)
	{
		if (core->data.init_angle > 360.0)
			core->data.init_angle = 0.0;
		core->data.init_angle += ROT_SPEED;
	}
	if (core->move.rotation_r)
	{
		if (core->data.init_angle < 0.0)
			core->data.init_angle = 360.0;
		core->data.init_angle -= ROT_SPEED;
	}
	dir_x = cos(core->data.init_angle * PI / 180.0);
	dir_y = sin(core->data.init_angle * PI / 180.0);
	core->data.move_dir_x = dir_x;
	core->data.move_dir_y = dir_y;
	if (core->move.up)
		up(core, dir_x, dir_y);
	if (core->move.down)
		down(core, dir_x, dir_y);
	left_right(core, dir_x, dir_y);
}
