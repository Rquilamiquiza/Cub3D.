/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:47 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/01 12:28:40 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "../mlx/mlx.h"
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"

#define RESET "\033[0m"
#define RED "\033[31m"

#define WIDTH 1200
#define HEIGHT 900
#define BLOCK 32
#define MAP_WIDTH 9
#define MAP_HEIGHT 6
#define PI 3.14159265
#define MOVE_SPEED 0.05
#define ROT_SPEED 1.5
#define TEX_SIZE 32

#define LINE_TEXTURE 4
#define LINE_COLOR 2
#define LINE_HEADER 6

#define MISSING_ARG "Missing Arguments\n"
#define MAP_ERROR "Map Error\n"

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef struct s_data
{
	double initAngle;
	int stepX;
	int stepY;
	int playerx;
	int playery;
	int tileY;
	int tileX;
	int lines_map;
	int column_map;
	double raydirX;
	double raydirY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double cameraX;
	double cameraY;
	double DirX;
	double DirY;
	double posX;
	double posY;
	double planX;
	double planY;
	double fov;

	int side;
	int line_height;
	int draw_start;
	int draw_end;

	double WallDist;
	double perpWallDist;

	int wall_height;
	char **map_full;
	char **map_texture;
	char **map_color;
	char **map_main;
} t_data;

typedef struct s_move
{
	float newStepX;
	float newStepY;
	int up;
	int down;
	int left;
	int right;
	int rotation_l;
	int rotation_r;
} t_move;

typedef struct s_img
{
	void *img;
	int *addr;

	int bpp;
	int line_height;
	int endian;

	int pixel_bits;
	int size_line;

	int height;
	int width;
} t_img;

typedef struct s_texinfo
{
	char *north;
	char *south;
	char *west;
	char *east;
	int *floor;
	int *ceiling;
	unsigned long hex_floor;
	unsigned long hex_ceiling;
	int size;
	int index;
	double step;
	double pos;
	int x;
	int y;
} t_texinfo;

typedef struct s_core
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int line_size;
	int bpp;
	int endian;
	int sky;
	int floor;
	int color;

	int **texture_pixels;
	int **textures;
	t_img imgs[4];

	int win_width;
	int win_height;

	t_move move;
	t_data data;
	t_texinfo texinfo;
} t_core;

void print_window(t_core *core);
void put_pixel(t_core *core, int x, int y, int color);
void raycasting(t_core *core);
void draw_map(t_core *core);
void ft_readmap(char *file, t_data *data);
void free_mtx(char **map);
void find_player(t_data *data);
void moviments(t_core *core);
int close_window(t_core *core);
int scalling(int old[2], int new[2], int value);
int texture_pixel(t_core *core, int x, int y, char *filename);
void init_texture(t_core *core);
void init_texinfo(t_texinfo *textures);
void init_core(t_core *core);
void free_tab(void **tab);
void init_data(t_core *core);
void update_texture_pixels(t_core *core, t_texinfo *tex, int x);
void init_texture_pixels(t_core *core);
void init_img_clean(t_img *img);
int load_texture(t_core *core, int tex_num, char *path);
int load_textures(t_core *core);
int validate_chater(t_data *data);
int validate_borders(t_data *data);
void print_matriz(char **map);
int error_msg_fd(char *msg, int fd);
int texture_validator(t_data *data);
char *last_word(char *str);
char *first_word(char *str);
int get_index_texture(char *str);
int color_validator(t_data *data);
int color_validator(t_data *data);
int convert_color(char *str);
#endif
