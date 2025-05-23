/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:47 by rquilami          #+#    #+#             */
/*   Updated: 2025/05/22 16:23:06 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include "../mlx/mlx.h"
# include "../get_next_line/get_next_line.h"

# define RESET "\033[0m"
# define RED "\033[31m"

#define WIDTH 1200
#define HEIGHT 900
#define BLOCK 32
#define MAP_WIDTH 9
#define MAP_HEIGHT 6
#define PI 3.14159265
#define MOVE_SPEED 0.05
#define ROT_SPEED 1.5


typedef struct 	s_data
{
	double	initAngle;
	int 	stepX;
	int 	stepY;
	int		playerx;
	int		playery;
	int 	tileY;
	int		tileX;
	int		lines_map;
	int		column_map;
	double	raydirX;
	double	raydirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	cameraX;
	double	cameraY;
	double		DirX;
	double		DirY;
	double   posX;
	double 	posY;
	double	planX;
	double	planY;
	double	fov;
	
	int		wall_height;
	char		**map;
}				t_data;

typedef struct s_move
{
	float newStepX;
	float newStepY;
	int up;
	int down;
	int left;
	int	right;
	int rotation_l;
	int rotation_r;
}			t_move;



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
	t_move		move;
	t_data		data;
}               t_core;


void    print_window(t_core *core);
void	put_pixel(t_core *core, int x, int y, int color);
void 	raycasting(t_core *core);
void	draw_map(t_core *core);
void	ft_readmap(char *file, t_data *data);
void	free_mtx(char **map);
void 	find_player(t_data *data);
void    moviments(t_core *core);
int 	close_window(t_core *core);

#endif
