/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:24 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/01 08:11:35 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"
int is_valid(char c)
{
    if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
        return (0); // Caractere inválido
    return (1);
}

int validate_chater(t_data *data)
{
    int i, j;
    int player_count;
    char c;

    i = 0;
    player_count = 0;
    while (i < data->lines_map)
    {
        j = 0;
        while (j < data->column_map)
        {
            c = data->map_main[i][j];
            if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ' && c != '\t' && c != '\n' && c != '\0')
                return (0); // Caractere inválido
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                player_count++;
            j++;
        }
        i++;
    }
    if (player_count != 1)
        return (0); // Deve haver exatamente um jogador
    return (1);
}

int border_zero(char **map, int i, int j)
{
    if (!(i != 0 && is_valid(map[i - 1][j])))
        return (0);
    if (map[i + 1] == NULL || map[i + 1][j] == '\0' || !is_valid(map[i + 1][j])) // ou algum outro valor padrão
        return (0);
    if (!(j != 0 && is_valid(map[i][j - 1])))
        return (0);
    if (!map[i][j + 1] || !is_valid(map[i][j + 1]))
        return (0);

    if (i != 0 && j != 0) // vericar as diagonais
    {
        if (!is_valid(map[i - 1][j - 1]))
            return (0);
        if (!is_valid(map[i + 1][j - 1]))
            return (0);
    }
    if (!map[i - 1][j + 1] || !is_valid(map[i - 1][j + 1]))
        return (0);
    if (!map[i + 1][j + 1] || !is_valid(map[i + 1][j + 1]))
        return (0);
    return (1);
}

int is_player_or_zero(char c)
{
    if (c == '0' || c == 'N' ||
        c == 'S' || c == 'E' || c == 'W')
        return (1);
    return (0);
}

int validate_borders(t_data *data)
{
    int i, j;

    i = 0;
    while (i < data->lines_map)
    {
        j = 0;
        while (j < data->column_map)
        {

            if (is_player_or_zero(data->map_main[i][j]))
                if (!border_zero(data->map_main, i, j))
                    return (0);
            j++;
        }
        i++;
    }
    return (1);
}
