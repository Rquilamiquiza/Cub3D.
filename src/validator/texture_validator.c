/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 08:38:21 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/26 15:28:36 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

char	*first_word(char *str)
{
	int		i;
	int		len;
	int		start;
	char	*word;

	i = 0;
	len = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	start = i;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		len++;
		i++;
	}
	word = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		word[i] = str[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*last_word(char *str)
{
	int		i;
	int		end;
	int		len;
	int		j;
	char	*word;

	i = ft_strlen(str) - 1;
	j = 0;
	len = 0;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i--;
	if (i < 0)
		return (NULL);
	end = i;
	while (i >= 0 && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i--;
	len = end - (i + 1) + 1;
	word = malloc(sizeof(char) * (len + 1));
	while (j < len)
	{
		word[j] = str[(i + 1) + j];
		j++;
	}
	word[len] = '\0';
	return (word);
}

int	has_extension(const char *filename, const char *ext)
{
	size_t	len_filename;
	size_t	len_ext;

	len_filename = (int)ft_strlen(filename);
	len_ext = (int)ft_strlen(ext);
	if (len_filename < len_ext)
		return (0);
	return (ft_strcmp(filename + len_filename - len_ext, ext) == 0);
}

int	file_ok(const char *filename)
{
	int		fd;
	char	buffer[1];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	if (read(fd, buffer, 1) == 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}



int	texture_validator(t_data *data)
{
	char	*way;
	int		i;
	int		index;

	i = 0;
	while (data->map_texture[i] && i < 6)
	{
		index = get_index_texture(data->map_texture[i]);
		if (index < 0)
			return (0);
		if (index < 4)
		{
			way = last_word(data->map_texture[i]);
			if (!file_ok(way) || !has_extension(way, ".xpm")
				|| count_words(data->map_texture[i]) != 2
				|| texture_dup(data->map_texture, 6) == 0)
			{
				free(way);
				return (0);
			}
			free(way);
		}
		else if(color_validator(data, i) == 0)
			return (0);
		i++;
	}
	return (1);
}
