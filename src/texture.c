/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:25:59 by jsoares           #+#    #+#             */
/*   Updated: 2025/05/24 21:09:23 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

// {{*FUNCAO PARA AJUSTAR AS IMAGENS E ELA NAO SE DESTORCER*}}
int scalling(int old[2], int new[2], int value)
{
    int deltaOld;
    int deltaNew;
    int oldValue;
    int rescaling;

    deltaOld = old[1] - old[0];
    deltaNew = new[1] - new[0];
    oldValue = value - old[0];

    rescaling = new[0] + ((oldValue * deltaNew) / deltaOld);
    return (rescaling);
}

int get_pixel_color(t_img *img, int x, int y)
{
    char *pixel;
    int color;

    pixel = img->addr + (y * img->line_height + x * (img->bpp / 8));
    color = *(unsigned int *)pixel;
    return (color);
}

int texture_pixel(t_core *core, int x, int y, char *filename)
{
    t_img texture_img;
    void *xpm;
    int color;

    xpm = mlx_xpm_file_to_image(core->mlx, filename, &texture_img.width, &texture_img.height);
    if (!xpm)
        return (printf("Error de textura\n")), 1;
    texture_img.img = xpm;
    texture_img.addr = mlx_get_data_addr(texture_img.img, &texture_img.bpp, &texture_img.line_height, &texture_img.endian);
    (void)x;
    (void)y;
    color = get_pixel_color(&texture_img, 0, 0);
    return (color);
}
