/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:35:32 by jsoares           #+#    #+#             */
/*   Updated: 2025/05/25 00:08:53 by jsoares          ###   ########.fr       */
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

void img_clean(t_img *img)
{
    img->img = NULL;
    img->addr = NULL;
    img->pixel_bits = 0;
    img->size_line = 0;
    img->endian = 0;
}

void init_texture_image(t_core *core, t_img *img, char *path)
{
    img_clean(img);
    img->img = mlx_xpm_file_to_image(core->mlx, path, &core->texinfo.size, &core->texinfo.size);
    if (img->img == NULL)
        return; //{{COLOCAR A FUNCAO QUE FAZ LIMPEZA}}
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_height, &img->endian);
    return;
}

static int *xpm_to_img(t_core *core, char *path)
{
    t_img tmp;
    int *buffer;
    int x;
    int y;

    init_texture_image(core, &tmp, path);
    buffer = calloc(1, sizeof *buffer * power(core->texinfo.size, 2));
    if (!buffer)
        return; //{{COLOCAR A FUNCAO QUE FAZ LIMPEZA}}
    y = 0;

    while (y < core->texinfo.size)
    {
        x = 0;
        while (x < core->texinfo.size)
        {
            buffer[y * core->texinfo.size + x] = tmp.addr[y * core->texinfo.size + x];
            x++;
        }
        y++;
    }
    mlx_destroy_image(core->mlx, tmp.img);
    return (buffer);
}


t_img load_texture(t_core *core, char *filename)
{
    t_img img;
    void *xpm = mlx_xpm_file_to_image(core->mlx, filename, &img.width, &img.height);
    if (!xpm)
        exit(write(2, "Erro ao carregar textura\n", 25));
    img.img = xpm;
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_height, &img.endian);
    return (img);
}
//{{FUNCAO PARA INICIO DA TEXTURA}}
void init_texture(t_core *core)
{
    core->textures = calloc(5, sizeof *core->textures);
    if (!core->textures)
        return; //{{COLOCAR A FUNCAO QUE FAZ LIMPEZA}}

    core->texinfo.north = "images/kaka.xpm";
    core->texinfo.south = "images/kaka.xpm";
    core->texinfo.east = "images/kaka.xpm";
    core->texinfo.west = "images/kaka.xpm";
    core->textures[NORTH] = xpm_to_img(core, core->texinfo.north);
    core->textures[SOUTH] = xpm_to_img(core, core->texinfo.south);
    core->textures[EAST] = xpm_to_img(core, core->texinfo.east);
    core->textures[WEST] = xpm_to_img(core, core->texinfo.west);
}