/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:31:22 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/07 12:28:47 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

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
	printf("Mapa lido com sucesso, column: %i, lines: %i", data->column_map, data->lines_map);
}

int find_player(int *px, int *py, t_data *data)
{
    int y = 0;
    int x = 0;
    while (y < data->column_map)
    {
        x = 0;
        while (x < data->lines_map)
        {
            if (data->map[y][x] == 'N' || data->map[y][x] == 'E' || data->map[y][x] == 'W' || data->map[y][x] == 'S')
            {
                *px = x;
                *py = y;
                return 1;
            }
            x++;
        }
        y++;
    }
    return 0;
}

int	ft_getAngle(char c)
{
	if (c == 'N')
		return (270);
	if (c == 'S')
		return (90);
	if (c == 'W')
		return (180);
	if (c == 'E')
		return (0);
	return (0);
}