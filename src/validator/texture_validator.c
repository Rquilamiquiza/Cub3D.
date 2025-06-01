/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 08:38:21 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/01 17:26:05 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

char *first_word(char *str)
{
    int i = 0;
    int start, len = 0;
    char *word;
    
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;

    start = i;
    while (str[i] && str[i] != ' ' && str[i] != '\t')
    {
        len++;
        i++;
    }
    word = malloc(len + 1);
    if (!word)
        return NULL;
    i = 0;
    while (i < len)
    {
        word[i] = str[start + i];
        i++;
    }
    word[i] = '\0';
    return word;
}

char *last_word(char *str)
{
    int i = strlen(str) - 1;
    int end, len = 0;
    char *word;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
        i--;
    if (i < 0)
        return NULL;
    end = i;
    while (i >= 0 && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        i--;
    i++; // i agora aponta para o início da última palavra
    len = end - i + 1;

    word = malloc(len + 1);
    if (!word)
        return NULL;
    for (int j = 0; j < len; j++)
        word[j] = str[i + j];
    word[len] = '\0';
    return word;
}

int has_extension(const char *filename, const char *ext)
{
    size_t len_filename = strlen(filename);
    size_t len_ext = strlen(ext);
    if (len_filename < len_ext)
        return 0;
    return strcmp(filename + len_filename - len_ext, ext) == 0;
}

int file_ok(const char *filename)
{
    int fd;
    fd = open(filename, O_RDONLY);
    char buffer[1];
    if (fd < 0)
        return (0);
    if (read(fd, buffer, 1) == 0)
    {
        close(fd);
        return (0); // vazio
    }
    close(fd);
    return (1); // não está vazio
}

int texture_validator(t_data *data)
{
    int i;
    char *way;

    i = 0;
    while (data->map_texture[i] && i < 4)
    {
        way = last_word(data->map_texture[i]);
        if (!file_ok(way) || !has_extension(way, ".xpm"))
        {
            free(way);
            return (0);
        }
        i++;
        free(way);
    }
    return (1);
}