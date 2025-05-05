/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:31:22 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/01 11:35:08 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

int	pos(char *file)
{
	int		i;
	int		fd;
	char	*tmp;

	i = 0;
	fd = open(file, O_RDONLY);
	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

char	**ft_readmap(char *file)
{
	char	**map;
	int		fd;
	int		lines;
	int		i;

	fd = open(file, O_RDONLY);
	lines = pos(file);
	if (fd < 0)
	{
		printf(RED "Error: file not found\n" RESET);
		exit(-1);
	}
	i = 0;
	map = malloc(sizeof(char *) * (lines + 2));
	map[i] = get_next_line(fd);
	if (!map[i])
		(free_mtx(map), (close(fd),
				printf(RED "ERROR!\nFile_empty\n" RESET, 2), exit(-1)));
	while (map[i])
	{
		i++;
		map[i] = get_next_line(fd);
	}
	close(fd);
	return (map);
}

int	*ft_pos(t_data *data)
{
	int	y;
	int	x;
	int	*pos;

	pos = malloc(sizeof(int) * 2);
	if (pos == NULL)
		return (NULL);
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x] && data->map[y][x] != '\n')
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'W' || data->map[y][x] == 'E')
			{
				pos[0] = x;
				pos[1] = y;
				return (pos);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

int	ft_return_angle(char c)
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