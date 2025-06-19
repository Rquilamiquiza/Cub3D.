/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:50:30 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/16 17:50:00 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

void	find_player(t_data *data)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	if (data->map_main == NULL)
		exit(0);
	while (data->map_main[y] && y < data->lines_map)
	{
		x = 0;
		while (data->map_main[y][x] && x < data->column_map)
		{
			if (data->map_main[y][x] == 'N' || data->map_main[y][x] == 'E'
				|| data->map_main[y][x] == 'W' || data->map_main[y][x] == 'S')
			{
				data->pos_x = x + 0.5f;
				data->pos_y = y + 0.5f;
				ft_get_angle(data, data->map_main[y][x]);
			}
			x++;
		}
		y++;
	}
}

void	get_lines_and_column(char *file, t_data *data)
{
	int		i;
	int		fd;
	char	*tmp;

	i = 0;
	fd = open(file, O_RDONLY);
	tmp = get_next_line(fd);
	data->column_map = (int)ft_strlen(tmp) - 1;
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		i++;
	}
	data->lines_map = i;
	close(fd);
}

void	ft_readmap(char *file, t_data *data)
{
	int	fd;
	int	i;

	fd = open(file, O_RDONLY);
	get_lines_and_column(file, data);
	if (fd < 0)
		return ;
	i = 0;
	data->map_full = malloc(sizeof(char *) * (data->lines_map + 2));
	data->map_full[i] = get_next_line(fd);
	if (!data->map_full[i])
	{
		printf("Error: file empty\n");
		return ;
	}
	while (data->map_full[i])
	{
		i++;
		data->map_full[i] = get_next_line(fd);
	}
	parsing_map(data);
	find_player(data);
	close(fd);
}
