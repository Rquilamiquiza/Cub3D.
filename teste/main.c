/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:05:02 by jsoares           #+#    #+#             */
/*   Updated: 2025/05/23 16:37:05 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../mlx/mlx.h"
#define WIDTH 800
#define HEIGHT 500

typedef struct s_img
{
    void *img;
    char *add;
    int bpp;
    int line_height;
    int endian;
    int width;
    int height;
} t_img;

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->add + (y * img->line_height + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

int get_pixel_color(t_img *img, int x, int y)
{
    char *pixel;
    int color;

    pixel = img->add + (y * img->line_height + x * (img->bpp / 8));
    color = *(unsigned int *)pixel;
    return color;
}

int map(int old[2], int new[2], int value)
{
    int deltaOld = old[1] - old[0];
    int deltaNew = new[1] - new[0];
    int oldValue = value - old[0];
    int response;

    response = new[0] + ((oldValue * deltaNew)/deltaOld);
    return response;
}

int main(void)
{
    t_img img;     // imagem de destino
    t_img xpm_img; // imagem fonte
    void *xpm;
    int y, x;
    int zy, zx;

    void *mlx = mlx_init();
    void *mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Justino");

    // Criar imagem onde vamos desenhar
    img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
    img.add = mlx_get_data_addr(img.img, &img.bpp, &img.line_height, &img.endian);

    // Carregar imagem XPM
    xpm = mlx_xpm_file_to_image(mlx, "images/blue_bricks.xpm", &xpm_img.width, &xpm_img.height);
    if (!xpm)
    {
        write(2, "Erro ao carregar imagem XPM\n", 29);
        return (1);
    }
    xpm_img.img = xpm;
    xpm_img.add = mlx_get_data_addr(xpm_img.img, &xpm_img.bpp, &xpm_img.line_height, &xpm_img.endian);

    // Copiar pixel a pixel
    for (y = 0; y < xpm_img.height; y++)
    {
        for (x = 0; x < xpm_img.width; x++)
        {
            int color = get_pixel_color(&xpm_img, x, y);
            zx = map((int[]){0,xpm_img.width}, (int[]){0, WIDTH}, x);
            zy = map((int[]){0,xpm_img.height}, (int[]){0, HEIGHT}, y);
            my_mlx_pixel_put(&img, zx, zy, color);
        }
    }
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
    return 0;
}