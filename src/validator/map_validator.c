/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:24 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/26 16:39:21 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

int	is_valid(char c)
{
	if (!c)
		return (0);
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	return (1);
}

int	validate_chater(t_data *data)
{
	int		player_count;
	int		i;
	int		j;
	char	c;

	i = 0;
	player_count = 0;
	while (data->map_main[i] && i < data->lines_map)
	{
		j = 0;
		while (data->map_main[i][j] && j < (int)ft_strlen(data->map_main[i]))
		{
			c = data->map_main[i][j];
			if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E'
				&& c != 'W' && c != ' ' && c != '\t' && c != '\n' && c != '\0')
				return (0);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (0);
	return (1);
}

int	border_zero(char **map, int i, int j)
{
	if (i == 0 || !is_valid(map[i - 1][j]))
		return (0);
	if (map[i + 1] == NULL || map[i + 1][j] == '\0' || !is_valid(map[i + 1][j])
		|| (int)ft_strlen(map[i + 1]) < j)
		return (0);
	if (!(j != 0 && is_valid(map[i][j - 1])))
		return (0);
	if (!map[i][j + 1] || !is_valid(map[i][j + 1]))
		return (0);
	return (1);
}

int	is_player_or_zero(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	validate_borders(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map_main[i] && i < data->lines_map)
	{
		j = 0;
		while (data->map_main[i][j] && j < (int)ft_strlen(data->map_main[i]))
		{
			if (is_player_or_zero(data->map_main[i][j]))
				if (!border_zero(data->map_main, i, j))
					return (0);
			j++;
		}
		if (data->map_main[i][0] == '\n' || data->map_main[i][0] == '\0')
			if (!line_between_the_map(data, i))
				return (0);
		i++;
	}
	return (1);
}
