# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 16:43:45 by rquilami          #+#    #+#              #
#    Updated: 2025/05/07 12:45:10 by rquilami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d
SRC = src/main.c src/screen.c src/raycasting.c src/free.c src/map.c src/move.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

GETNEXTLINE_DIR = get_next_line
GETNEXTLINE = $(GETNEXTLINE_DIR)/get_next_line.a
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a

all: $(MLX_LIB) $(NAME)


$(NAME): $(OBJ) $(GETNEXTLINE)
	$(CC) $(CFLAGS) $(OBJ) $(GETNEXTLINE) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -o $(NAME)


$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)
	
$(GETNEXTLINE):
	make -C $(GETNEXTLINE_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean
	make -C $(GETNEXTLINE_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(GETNEXTLINE_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

