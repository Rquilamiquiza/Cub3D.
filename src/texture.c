/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:25:59 by jsoares           #+#    #+#             */
/*   Updated: 2025/06/01 11:42:47 by justinosoar      ###   ########.fr       */
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