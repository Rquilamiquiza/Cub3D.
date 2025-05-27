/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:25:59 by jsoares           #+#    #+#             */
/*   Updated: 2025/05/27 21:16:53 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

int load_textures(t_core *core)
{
    if (!load_texture(core, 0, "images/black_bricks.xpm") ||
        !load_texture(core, 1, "images/blue_hole.xpm") ||
        !load_texture(core, 2, "images/sama.xpm") ||
        !load_texture(core, 3, "images/wall.xpm"))
    {
        printf("Error loading textures\n");
        return (0);
    }
    return (1);
}