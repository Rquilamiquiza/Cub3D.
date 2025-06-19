# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 16:43:45 by rquilami          #+#    #+#              #
#    Updated: 2025/06/18 14:37:51 by jsoares          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D
SRC = src/main.c src/raycasting.c src/move.c src/map.c src/screen.c src/free/free.c \
		src/texture.c src/init/init_core.c src/free/free_data.c \
		src/utils/error.c src/validator/map_validator.c src/validator/texture_validator.c \
		src/validator/color_validator.c src/events/event_hook.c src/utils/ft_isspace.c \
		src/move_verify.c \
		src/maps/ft_readmap.c src/maps/parsing_map.c src/raycasting/draw_wall.c src/raycasting/dda.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

GETNEXTLINE_DIR = get_next_line
GETNEXTLINE = $(GETNEXTLINE_DIR)/get_next_line.a
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)


$(NAME): $(OBJ) $(GETNEXTLINE)
	$(CC) $(CFLAGS) $(OBJ) $(GETNEXTLINE) $(LIBFT_LIB) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -o $(NAME)


$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)
$(GETNEXTLINE):
	make -C $(GETNEXTLINE_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean
	make -C $(GETNEXTLINE_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(GETNEXTLINE_DIR) fclean
	

re: fclean all

.PHONY: all clean fclean re

