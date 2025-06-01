/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:25:59 by jsoares           #+#    #+#             */
/*   Updated: 2025/06/01 17:27:48 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

int get_index_texture(char *str)
{
    char *word;

    word = first_word(str);
    if (!ft_strncmp(word, "NO", 2))
        return (0);
    else if (!ft_strncmp(word, "SO", 2))
        return (1);
    else if (!ft_strncmp(word, "WE", 2))
        return (2);
    else if (!ft_strncmp(word, "EA", 2))
        return (3);
    else
        return (-1);
    free(word);
}

int load_texture(t_core *core, int tex_num, char *path)
{
    t_img *tex;
    
    tex = &core->imgs[tex_num];

    tex->img = mlx_xpm_file_to_image(core->mlx, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Error: Could not load texture %s\n", path);
        return (0);
    }
    tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp,
                                         &tex->line_height, &tex->endian);
    return (1);
}

int load_textures(t_core *core)
{
    int i;
    int index;
    char *word;

    i = 0;
    while (i < 4 && core->data.map_texture[i])
    {
        index = get_index_texture(core->data.map_texture[i]);
        if (index < 0)
        {
            printf("algo de errado\n");
            return (0);
        }
        word = last_word(core->data.map_texture[i]);
        if (!load_texture(core, index, word))
        {
            printf("Erro a carregar a textura");
            free(word);
            return (0);
        }
        i++;
        free(word);
    }
    return (1);
}
