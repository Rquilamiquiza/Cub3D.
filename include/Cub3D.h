/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:47 by rquilami          #+#    #+#             */
/*   Updated: 2025/04/29 19:23:05 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../mlx/mlx.h"
# define WIDTH 1300
# define HEIGTH 1100

typedef struct core_s
{
    void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			line_size;
	int			bpp;
	int			endian;
	int			sky;
	int			floor;
	int			color;
}               core_t;


void    print_window(core_t *core);


#endif
