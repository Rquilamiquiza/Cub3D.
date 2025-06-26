/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:14:44 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/26 15:39:48 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

void	put_pixel(t_core *core, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= core->win_width || y < 0 || y >= core->win_height)
		return ;
	pixel = core->addr + (y * core->line_size + x * (core->bpp / 8));
	*(unsigned int *)pixel = color;
}

int	convert_color(char *str)
{
	char	*color;
	char	**split;
	int		r;
	int		g;
	int		b;

	color = last_word(str);
	split = ft_split(color, ',');
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_mtx(split);
	free(color);
	return ((r << 16) | (g << 8) | b);
}

void	init_color(t_core *core)
{
	char	*word;
	int		index;
	int		i;

	i = 0;
	while (i < 6 && core->data.map_texture[i])
	{
		index = get_index_texture(core->data.map_texture[i]);
		word = first_word(core->data.map_texture[i]);
		if (index == 4)
			core->floor = convert_color(core->data.map_texture[i]);
		else if (index == 5)
			core->sky = convert_color(core->data.map_texture[i]);
		i++;
		free(word);
	}
}

void	print_window(t_core *core)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	init_color(core);
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				core->color = core->sky;
			else
				core->color = core->floor;
			put_pixel(core, x, y, core->color);
			x++;
		}
		x = 0;
		y++;
	}
}
