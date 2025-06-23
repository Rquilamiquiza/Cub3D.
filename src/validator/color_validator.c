/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:44:09 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/23 10:30:04 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

int	count_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		i++;
	return (i);
}

int	valid_color(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
		{
			if (color[i] != ' ' && color[i] != '\t')
				return (0);
		}
		i++;
	}
	return (1);
}

int	color_ok(char *color)
{
	char	**split;
	int		i;
	int		atoi;

	i = 0;
	split = ft_split(color, ',');
	if (count_mtx(split) != 3)
	{
		free_mtx(split);
		return (0);
	}
	while (i < 3)
	{
		atoi = ft_atoi(split[i]);
		if (atoi > 255 || atoi < 0 || !valid_color(split[i]))
		{
			free_mtx(split);
			return (0);
		}
		i++;
	}
	free_mtx(split);
	return (1);
}

int	has_color(char *str)
{
	char	*dir;

	dir = first_word(str);
	if ((!ft_strcmp(dir, "C") || !ft_strcmp(dir, "F")) && ft_strlen(dir) == 1)
	{
		free(dir);
		return (1);
	}
	free(dir);
	return (0);
}

int	color_validator(t_data *data)
{
	int		i;
	char	*way;

	i = 0;
	while (data->map_color[i] && i < 2)
	{
		way = last_word(data->map_color[i]);
		if (!color_ok(way) || count_words(data->map_color[i]) != 2
			|| !has_color(data->map_color[i]))
		{
			free(way);
			return (0);
		}
		i++;
		free(way);
	}
	return (1);
}
