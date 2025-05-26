/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:35:32 by jsoares           #+#    #+#             */
/*   Updated: 2025/05/26 12:14:24 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

int power(int value, int expo)
{
    int i;
    int res;

    i = 0;
    res = 1;
    while (i < expo)
    {
        res *= value;
        i++;
    }
    return (res);
}

void init_img_clean(t_img *img)
{
    img->img = NULL;
    img->addr = NULL;
    img->pixel_bits = 0;
    img->size_line = 0;
    img->endian = 0;
}

void init_texture_img(t_core *core, t_img *image, char *path)
{
    void *xpm;
    init_img_clean(image);

    xpm = mlx_xpm_file_to_image(core->mlx, path, &image->width,
                                &image->height);
    if (!xpm)
    {
        printf("Erro pegar imagem");
        return;
    }
    image->img = xpm;
    image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
                                           &image->size_line, &image->endian);
    return;
}

static int *xpm_to_img(t_core *core, char *path)
{
    t_img tmp;
    int *buffer;
    int x;
    int y;

    init_texture_img(core, &tmp, path);
    buffer = ft_calloc(1,
                       sizeof *buffer * core->texinfo.size * core->texinfo.size);
    if (!buffer)
    {
        printf("Erro ao alocar buffer");
        return NULL;
    }
    y = 0;
    while (y < core->texinfo.size)
    {
        x = 0;
        while (x < core->texinfo.size)
        {
            buffer[y * core->texinfo.size + x] = tmp.addr[y * core->texinfo.size + x];
            ++x;
        }
        y++;
    }
    mlx_destroy_image(core->mlx, tmp.img);
    return (buffer);
}

void init_texture(t_core *core)
{
    core->textures = ft_calloc(5, sizeof *core->textures);
    if (!core->textures)
    {
        printf("Erro ao alocar texturas");
        return;
    }
    core->textures[NORTH] = xpm_to_img(core, "images/kaka.xpm");
    core->textures[SOUTH] = xpm_to_img(core, "images/kaka.xpm");
    core->textures[EAST] = xpm_to_img(core, "images/kaka.xpm");
    core->textures[WEST] = xpm_to_img(core, "images/kaka.xpm");
}



