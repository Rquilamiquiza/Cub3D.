/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:25:59 by jsoares           #+#    #+#             */
/*   Updated: 2025/06/26 15:02:23 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

int	get_index_texture(char *str)
{
	char	*word;
	int		index;

	index = -1;
	word = first_word(str);
	if (!ft_strcmp(word, "NO") && ft_strlen(word) == 2)
		index = 0;
	else if (!ft_strcmp(word, "SO") && ft_strlen(word) == 2)
		index = 1;
	else if (!ft_strcmp(word, "WE") && ft_strlen(word) == 2)
		index = 2;
	else if (!ft_strcmp(word, "EA") && ft_strlen(word) == 2)
		index = 3;
	else if (!ft_strcmp(word, "F") && ft_strlen(word) == 1)
		index = 4;
	else if (!ft_strcmp(word, "C") && ft_strlen(word) == 1)
		index = 5;
	free(word);
	return (index);
}

int	load_texture(t_core *core, int tex_num, char *path)
{
	t_img	*tex;

	tex = &core->imgs[tex_num];
	tex->img = mlx_xpm_file_to_image(core->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		error_msg_fd("Error: Could not load all textures", 2);
		return (0);
	}
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_height,
			&tex->endian);
	return (1);
}

int	load_textures(t_core *core)
{
	int		i;
	int		index;
	char	*word;

	i = 0;
	while (i < 6 && core->data.map_texture[i])
	{
		index = get_index_texture(core->data.map_texture[i]);
		if (index < 0)
		{
			error_msg_fd("Error : Invalid Word\n", 2);
			return (0);
		}
		word = last_word(core->data.map_texture[i]);
		if (index < 4)
		{
			if (!load_texture(core, index, word))
			{
				free(word);
				return (0);
			}
		}
		i++;
		free(word);
	}
	return (1);
}
