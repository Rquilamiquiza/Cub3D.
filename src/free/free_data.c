/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:00:42 by jsoares           #+#    #+#             */
/*   Updated: 2025/06/22 08:33:02 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void clean_resources(t_core *core)
{
	if (core->win)
		mlx_destroy_window(core->mlx, core->win);
	if (core->img)
		mlx_destroy_image(core->mlx, core->img);
	if (core->mlx)
		mlx_destroy_display(core->mlx);
	if (core->data.map_full)
		free_mtx(core->data.map_full);
	if (core->data.map_color)
		free_map_aux(core->data.map_color, core->data.column_map);
	if (core->data.map_texture)
		free_map_aux(core->data.map_texture, core->data.column_map);
	if (core->data.map_main)
		free_map_aux(core->data.map_main, core->data.column_map);
	if (core)
		free(core);
	exit(1);
}
