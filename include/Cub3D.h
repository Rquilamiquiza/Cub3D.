/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:47 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/05 17:42:40 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../get_next_line/get_next_line.h"

# define RESET "\033[0m"
# define RED "\033[31m"

#define WIDTH 640
#define HEIGHT 480
#define BLOCK 32
#define MAP_WIDTH 9
#define MAP_HEIGHT 6
#define PI 3.14159265


typedef struct 	s_data
{
	float	initAngle;
	int		playerx;
	int		playery;
	char		**map;
}				t_data;

typedef struct	s_player
{
	int x;
	int y;
}				t_player;

typedef struct s_core
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
	t_player	player;
	t_data		data;
}               t_core;


void    print_window(t_core *core);
void	put_pixel(t_core *core, int x, int y, int color);
void	vision_player(t_core *core, float initAngle);
void	draw_map(t_core *core);

#endif
