/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:50:30 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/01 17:29:12 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

void find_player(t_data *data)
{
	int y;
	int x;

	x = 0;
	y = 0;
	if (data->map_main == NULL)
		exit(0);
	while (y < data->lines_map)
	{
		x = 0;
		while (x < data->column_map)
		{
			if (data->map_main[y][x] == 'N' || data->map_main[y][x] == 'E' || data->map_main[y][x] == 'W' || data->map_main[y][x] == 'S')
			{
				data->posX = x + 0.5f;
				data->posY = y + 0.5f;
				ft_getAngle(data, data->map_main[y][x]);
			}
			x++;
		}
		y++;
	}
}

void getLines_and_Column(char *file, t_data *data)
{
	int i;
	int fd;
	char *tmp;

	i = 0;
	fd = open(file, O_RDONLY);

	tmp = get_next_line(fd);
	data->column_map = strlen(tmp) - 1;
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		i++;
	}
	data->lines_map = i;
	close(fd);
}

void ft_readmap(char *file, t_data *data)
{
	int fd;
	int i;

	fd = open(file, O_RDONLY);
	getLines_and_Column(file, data);
	if (fd < 0)
	{
		printf(RED "Error: file not found\n" RESET);
		exit(-1);
	}
	i = 0;
	data->map_full = malloc(sizeof(char *) * (data->lines_map + 2));
	data->map_full[i] = get_next_line(fd);

	if (!data->map_full[i])
		(free_mtx(data->map_full), (close(fd),
									exit(-1)));
	while (data->map_full[i])
	{
		i++;
		data->map_full[i] = get_next_line(fd);
	}
	parsing_map(data);
	close(fd);
	find_player(data);
}
