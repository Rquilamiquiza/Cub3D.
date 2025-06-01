/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:31:22 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/01 08:32:17 by justinosoar      ###   ########.fr       */
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
int ft_isspace(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] != 32 && str[i] != '\t' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
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
	if (!map)
		return;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}

int map_texture(t_data *data, int i)
{
	int cont = 0;
	data->map_texture = ft_calloc(5, sizeof(char *));
	while (cont < LINE_TEXTURE && data->map_full[i])
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

int map_color(t_data *data, int i)
{
	int cont = 0;
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
}

int map_draw(t_data *data, int i)
{
	int cont = 0;
	int is = 1;
	int total_line;
	int line_map = data->lines_map - i;
	total_line = data->lines_map;
	data->lines_map = data->lines_map - i - 1;
	if (line_map <= 0)
		line_map = 1;
	data->map_main = ft_calloc(line_map + 2, sizeof(char *)); // +1 para NULL-terminador, se necessário
	if (!data->map_main)
		return (-1); // erro na alocação

	// Pula possíveis linhas em branco
	while (data->map_full[i])
	{
		if (ft_isspace(data->map_full[i]))
		{
			if (is)
			{
				data->column_map = ft_strlen(data->map_full[i]) - 1;
				is = 0;
				break;
			}
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

void parsing_texture(t_data *data)
{
	int i;

	i = 0;
	i = map_texture(data, i);
	i = map_color(data, i);
	i = map_draw(data, i);
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
	parsing_texture(data);
	close(fd);
	find_player(data);
}
