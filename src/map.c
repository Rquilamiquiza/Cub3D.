/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:31:22 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/01 17:24:26 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

void ft_getAngle(t_data *data, char c)
{
	if (c == 'N')
		data->initAngle = 270.0f;
	if (c == 'S')
		data->initAngle = 90.0f;
	if (c == 'W')
		data->initAngle = 180.0f;
	if (c == 'E')
		data->initAngle = 0.0f;
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






