/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:53:23 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/20 19:38:37 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

void	draw_texture(t_core *core, t_img *tex, int texX, int x)
{
	double	step;
	double	tex_pos;
	int		line_height;
	int		tex_y;
	int		y;

	line_height = core->data.draw_end - core->data.draw_start;
	if (line_height <= 0)
		return ;
	step = (double)tex->height / (double)line_height;
	tex_pos = (core->data.draw_start - HEIGHT / 2 + line_height / 2) * step;
	y = core->data.draw_start;
	while (y < core->data.draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex->color = get_pixel_color(tex, texX, tex_y);
		put_pixel(core, x, y, tex->color);
		tex_pos += step;
		y++;
	}
}

t_img	*define_texture(t_core *core, int side)
{
	t_img	*tex;

	if (side == 0)
	{
		if (core->data.raydir_x > 0)
			tex = &core->imgs[3];
		else
			tex = &core->imgs[2];
	}
	else
	{
		if (core->data.raydir_y > 0)
			tex = &core->imgs[1];
		else
			tex = &core->imgs[0];
	}
	return (tex);
}

void	draw_vertical_line(t_core *core, int x, int side)
{
	double	wall_x;
	int		tex_x;
	t_img	*tex;

	tex = define_texture(core, side);
	if (side == 0)
	{
		wall_x = core->data.pos_y + core->data.perp_wall_dist
			* core->data.raydir_y;
	}
	else
	{
		wall_x = core->data.pos_x + core->data.perp_wall_dist
			* core->data.raydir_x;
	}
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if ((side == 0 && core->data.raydir_x > 0) || (side == 1
			&& core->data.raydir_y < 0))
	{
		tex_x = tex->width - tex_x - 1;
	}
	draw_texture(core, tex, tex_x, x);
}

void	draw_wall(t_core *core, int x, int side)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	if (side == 0)
		core->data.perp_wall_dist = (core->data.tile_x - core->data.pos_x + (1
					- core->data.step_x) / 2) / core->data.raydir_x;
	else
		core->data.perp_wall_dist = (core->data.tile_y - core->data.pos_y + (1
					- core->data.step_y) / 2) / core->data.raydir_y;
	line_height = (int)(HEIGHT / core->data.perp_wall_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	core->data.draw_start = draw_start;
	core->data.draw_end = draw_end;
	core->data.line_height = line_height;
	core->data.side = side;
	draw_vertical_line(core, x, side);
}
