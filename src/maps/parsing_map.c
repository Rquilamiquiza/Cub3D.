/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:55:25 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/26 14:50:29 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

int	map_texture(t_data *data, int i)
{
	int	cont;

	cont = 0;
	data->map_texture = ft_calloc(7, sizeof(char *));
	while (cont < LINE_HEADER && data->map_full[i])
	{
		if (ft_isspace(data->map_full[i]))
		{
			data->map_texture[cont] = data->map_full[i];
			cont++;
		}
		i++;
	}
	return (i);
}

/*int	map_color(t_data *data, int i)
{
	int	cont;

	cont = 0;
	data->map_color = ft_calloc(3, sizeof(char *));
	while (cont < LINE_COLOR && data->map_full[i])
	{
		if (ft_isspace(data->map_full[i]))
		{
			data->map_color[cont] = data->map_full[i];
			cont++;
		}
		i++;
	}
	return (i);
}*/

int	map_draw(t_data *data, int i)
{
	int	cont;
	int	total_line;
	int	line_map;

	cont = 0;
	line_map = data->lines_map - i;
	total_line = data->lines_map;
	data->lines_map = data->lines_map - i - 1;
	data->map_main = ft_calloc(line_map + 2, sizeof(char *));
	while (data->map_full[i])
	{
		if (ft_isspace(data->map_full[i]))
		{
			data->column_map = ft_strlen(data->map_full[i]) - 1;
			break ;
		}
		i++;
	}
	while (cont < line_map && i < total_line && data->map_full[i])
	{
		data->map_main[cont] = data->map_full[i];
		cont++;
		i++;
	}
	return (i);
}

void	parsing_map(t_data *data)
{
	int	i;

	i = 0;
	i = map_texture(data, i);
	//i = map_color(data, i);
	i = map_draw(data, i);
	//print_matriz(data->map_texture);
}
