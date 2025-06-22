/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:47 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/22 08:33:35 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <ctype.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[31m"

# define WIDTH 1024
# define HEIGHT 768
# define BLOCK 32
# define MAP_WIDTH 9
# define MAP_HEIGHT 6
# define PI 3.14159265
# define MOVE_SPEED 0.05
# define ROT_SPEED 1.5
# define TEX_SIZE 32
# define TILE_SIZE 64

# define PLAYER_RADIUS 0.1f
# define SLIDE_X 1
# define SLIDE_Y 2
# define SLIDE_NOT 0

# define LINE_TEXTURE 4
# define LINE_COLOR 2
# define LINE_HEADER 6

# define MISSING_ARG "Missing Arguments\n"
# define MAP_ERROR "Map Error\n"
# define MAP_ERROR_PLAYER "Map Error : Invalid chater or invalid player\n"
# define MAP_ERROR_BORDER "Map Error : Invalid map\n"
# define MAP_ERROR_TEXTURE "Map Error : ERROR AT TEXTURE\n"
# define MAP_ERROR_COLOR "Map Error : ERROR AT COLOR\n"
# define FILE_ERROR "FILE ERROR\n"

enum				e_texture_index
{
	W = 119,
	S = 115,
	D = 97,
	E = 100,
	CLOSE = 65307
};

typedef struct s_data
{
	double			init_angle;
	int				step_x;
	int				step_y;
	int				playerx;
	int				playery;
	int				tile_y;
	int				tile_x;
	int				lines_map;
	int				column_map;
	double			raydir_x;
	double			raydir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			camera_x;
	double			camera_y;
	double			dir_x;
	double			dir_y;
	double			pos_x;
	double			pos_y;
	double			plan_x;
	double			plan_y;
	double			fov;

	float			move_dir_x;
	float			move_dir_y;

	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;

	double			wall_dist;
	double			perp_wall_dist;

	int				wall_height;
	char			**map_full;
	char			**map_texture;
	char			**map_color;
	char			**map_main;
}					t_data;

typedef struct s_move
{
	float			newstep_x;
	float			newstep_y;
	int				up;
	int				down;
	int				left;
	int				right;
	int				rotation_l;
	int				rotation_r;
}					t_move;

typedef struct s_img
{
	void			*img;
	int				*addr;

	int				bpp;
	int				line_height;
	int				endian;

	int				pixel_bits;
	int				size_line;

	int				height;
	int				width;
	int				color;
}					t_img;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}					t_texinfo;

typedef struct s_core
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				line_size;
	int				bpp;
	int				endian;
	int				sky;
	int				floor;
	int				color;
	float			next_x;
	float			next_y;

	int				**texture_pixels;
	int				**textures;
	t_img			imgs[4];

	int				win_width;
	int				win_height;

	t_move			move;
	t_data			data;
	t_texinfo		texinfo;
}					t_core;

void				print_window(t_core *core);
void				put_pixel(t_core *core, int x, int y, int color);
void				raycasting(t_core *core);
void				ft_readmap(char *file, t_data *data);
void				free_mtx(char **map);
void				find_player(t_data *data);
void				moviments(t_core *core);
int					close_window(t_core *core);
void				init_texinfo(t_texinfo *textures);
void				init_core(t_core *core);
void				free_tab(void **tab);
int					load_texture(t_core *core, int tex_num, char *path);
int					load_textures(t_core *core);
int					validate_chater(t_data *data);
int					validate_borders(t_data *data);
void				print_matriz(char **map);
int					error_msg_fd(char *msg, int fd);
int					texture_validator(t_data *data);
char				*last_word(char *str);
char				*first_word(char *str);
int					get_index_texture(char *str);
int					color_validator(t_data *data);
int					color_validator(t_data *data);
int					convert_color(char *str);
void				init_vars(t_core *core);
void				init_config(t_core *core);
int					press(int key, t_core *core);
int					release(int key, t_core *core);
int					ft_isspace(char *str);
void				ft_get_angle(t_data *data, char c);
void				parsing_map(t_data *data);
void				draw_wall(t_core *core, int x, int side);
unsigned int		get_pixel_color(t_img *tex, int x, int y);
void				dda(double fov, t_data *data, t_core *core);
int					has_extension(const char *filename, const char *ext);
int					file_ok(const char *filename);
void				free_map_aux(char **map, int len);
void				clean_textures(t_core *core);
void				exit_error(char *message, t_core *core);
int					ft_strcmp(const char *s1, const char *s2);
int					is_wall(float px, float py, t_core *core);
int					count_words(char *str);

void clean_resources(t_core *core);
#endif
