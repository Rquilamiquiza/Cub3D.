/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:36:05 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/19 13:43:08 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

void	up(t_core *core, float dir_x, float dir_y)
{
	core->move.newstep_x = core->data.pos_x + dir_x * MOVE_SPEED;
	core->move.newstep_y = core->data.pos_y + dir_y * MOVE_SPEED;
	if (core->move.newstep_x < 1)
		;
	else if (!is_wall(core->move.newstep_x, core->move.newstep_y, core,
			SLIDE_NOT))
	{
		core->data.pos_x = core->move.newstep_x;
		core->data.pos_y = core->move.newstep_y;
	}
	else if (!is_wall(core->move.newstep_x, core->data.pos_y, core, SLIDE_X))
	{
		core->data.pos_x = core->move.newstep_x;
	}
	else if (!is_wall(core->data.pos_x, core->move.newstep_y, core, SLIDE_Y))
	{
		core->data.pos_y = core->move.newstep_y;
	}
}

void	down(t_core *core, float dir_x, float dir_y)
{
	core->move.newstep_x = core->data.pos_x - dir_x * MOVE_SPEED;
	core->move.newstep_y = core->data.pos_y - dir_y * MOVE_SPEED;
	if (core->move.newstep_x < 1 || core->move.newstep_y < 1)
		;
	else if (!is_wall(core->move.newstep_x, core->move.newstep_y, core,
			SLIDE_NOT))
	{
		core->data.pos_x = core->move.newstep_x;
		core->data.pos_y = core->move.newstep_y;
	}
	else if (!is_wall(core->move.newstep_x, core->data.pos_y, core, SLIDE_X))
	{
		core->data.pos_x = core->move.newstep_x;
	}
	else if (!is_wall(core->data.pos_x, core->move.newstep_y, core, SLIDE_Y))
	{
		core->data.pos_y = core->move.newstep_y;
	}
}

void	up_down(t_core *core, float dir_x, float dir_y)
{
	if (core->move.up)
	{
		up(core, dir_x, dir_y);
	}
	if (core->move.down)
	{
		down(core, dir_x, dir_y);
	}
}

void	left_right(t_core *core, float dir_x, float dir_y)
{
	if (core->move.left)
	{
		core->move.newstep_x = core->data.pos_x - dir_y * MOVE_SPEED;
		core->move.newstep_y = core->data.pos_y + dir_x * MOVE_SPEED;
		if (!is_wall(core->move.newstep_x - 0.25, core->move.newstep_y + 0.25,
				core, SLIDE_NOT))
		{
			core->data.pos_x = core->move.newstep_x;
			core->data.pos_y = core->move.newstep_y;
		}
	}
	if (core->move.right)
	{
		core->move.newstep_x = core->data.pos_x + dir_y * MOVE_SPEED;
		core->move.newstep_y = core->data.pos_y - dir_x * MOVE_SPEED;
		if (!is_wall(core->move.newstep_x + 0.25, core->move.newstep_y - 0.25,
				core, SLIDE_NOT))
		{
			core->data.pos_x = core->move.newstep_x;
			core->data.pos_y = core->move.newstep_y;
		}
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
	up_down(core, dir_x, dir_y);
	left_right(core, dir_x, dir_y);
}
