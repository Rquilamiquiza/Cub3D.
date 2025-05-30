/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:31:22 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/30 16:20:26 by jsoares          ###   ########.fr       */
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
int ft_isspace(char *str)
{
	int i =0;

	while (str[i])
	{
		if (str[i] != 32 && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
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

void print_matriz(char **map)
{
	int i = 0;
	while(map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}

void parsing_texture(t_data *data)
{
	int i = 0;
	int cont = 0;
	data->map_texture = ft_calloc(5,  sizeof(char *));
	while(data->map_full[i]);
	// dividir e passar os elementos para cada parte da textura
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
	print_matriz(data->map_full);
	close(fd);
	find_player(data);
}
