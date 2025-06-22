/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:31:22 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/21 23:13:53 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

void ft_get_angle(t_data *data, char c)
{
	if (c == 'N')
		data->init_angle = 90.0f;
	if (c == 'S')
		data->init_angle = 270.0f;
	if (c == 'W')
		data->init_angle = 0.0f;
	if (c == 'E')
		data->init_angle = 180.0f;
}

void print_matriz(char **map)
{
	int i;

	i = 0;
	if (!map)
		return;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}
