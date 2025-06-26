/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:45:08 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/26 14:50:06 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

void	free_mtx(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
	map = NULL;
}

void	free_map_aux(char **map, int len)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		map[i] = NULL;
		free(map[i]);
		i++;
	}
	(void)len;
	free(map);
}

void	clean_textures(t_core *core)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(core->mlx, core->imgs[i].img);
		i++;
	}
}

void	exit_error(char *message, t_core *core)
{
	if (message)
		error_msg_fd(message, 2);
	if (core->data.map_full)
		free_mtx(core->data.map_full);
	//if (core->data.map_color)
	//	free_map_aux(core->data.map_color, core->data.column_map);
	if (core->data.map_texture)
		free_map_aux(core->data.map_texture, core->data.column_map);
	if (core->data.map_main)
		free_map_aux(core->data.map_main, core->data.column_map);
	if (core)
		free(core);
	exit(1);
}

int	close_window(t_core *core)
{
	if (core->img)
		mlx_destroy_image(core->mlx, core->img);
	if (core->win)
		mlx_destroy_window(core->mlx, core->win);
	clean_textures(core);
	if (core->mlx)
		mlx_destroy_display(core->mlx);
	free_mtx(core->data.map_full);
	//free_map_aux(core->data.map_color, core->data.column_map);
	free_map_aux(core->data.map_texture, core->data.column_map);
	free_map_aux(core->data.map_main, core->data.column_map);
	free(core->mlx);
	free(core);
	exit(0);
	return (0);
}
