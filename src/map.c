/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:31:22 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/22 13:55:49 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

void	ft_getAngle(t_data *data, char c)
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

void find_player(t_data *data)
{
    int y = 0;
    int x = 0;
	if (data->map == NULL)
	{
		printf("Ponteiro Nullo\n");
		exit(0);
	}
    while (y < data->lines_map)
    {
        x = 0;
        while (x < data->column_map)
        {
            if (data->map[y][x] == 'N' || data->map[y][x] == 'E' || data->map[y][x] == 'W' || data->map[y][x] == 'S')
            {
                data->posX = x + 0.5f;
                data->posY = y + 0.5f;
				ft_getAngle(data, data->map[y][x]);
            }
            x++;
        }
        y++;
    }
}

void	getLines_and_Column(char *file, t_data *data)
{
	int		i;
	int		fd;
	char	*tmp;

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

void	ft_readmap(char *file, t_data *data)
{
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	getLines_and_Column(file, data);
	if (fd < 0)
	{
		printf(RED "Error: file not found\n" RESET);
		exit(-1);
	}
	i = 0;
	data->map = malloc(sizeof(char *) * (data->lines_map + 2));
	data->map[i] = get_next_line(fd);
	if (!data->map[i])
		(free_mtx(data->map), (close(fd),
				 exit(-1)));
	while (data->map[i])
	{
		i++;
		data->map[i] = get_next_line(fd);
	}
	close(fd);
	find_player(data);
}
