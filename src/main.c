/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:41:46 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/23 07:36:53 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

int	main_loop(t_core *core)
{
	moviments(core);
	print_window(core);
	raycasting(core);
	mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);
	return (0);
}

int	validate_full_map(t_core *core)
{
	if (!texture_validator(&core->data))
	{
		error_msg_fd(MAP_ERROR_TEXTURE, 2);
		return (0);
	}
	if (!color_validator(&core->data))
	{
		error_msg_fd(MAP_ERROR_COLOR, 2);
		return (0);
	}
	if (!validate_chater(&core->data))
	{
		error_msg_fd(MAP_ERROR_PLAYER, 2);
		return (0);
	}
	if (!validate_borders(&core->data))
	{
		error_msg_fd(MAP_ERROR_BORDER, 2);
		return (0);
	}
	return (1);
}

int	file_validator(char *filename)
{
	if (!file_ok(filename) || !has_extension(filename, ".cub"))
	{
		error_msg_fd(FILE_ERROR, 2);
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_core	*core;

	if (argc != 2)
		return (error_msg_fd(MISSING_ARG, 2));
	core = ft_calloc(1, sizeof(t_core));
	init_core(core);
	if (!file_validator(argv[1]))
	{
		free(core);
		return (1);
	}
	ft_readmap(argv[1], &core->data);
	if (!validate_full_map(core))
		exit_error("", core);
	init_vars(core);
	init_config(core);
	if (!load_textures(core))
		clean_resources(core);
	mlx_hook(core->win, 17, 0, close_window, core);
	mlx_hook(core->win, 2, 1L << 0, press, core);
	mlx_hook(core->win, 3, 1L << 1, release, core);
	mlx_loop_hook(core->mlx, main_loop, core);
	mlx_loop(core->mlx);
	return (0);
}
