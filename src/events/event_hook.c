/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:38:27 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/04 08:30:08 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

int	press(int key, t_core *core)
{
	if (key == CLOSE)
		close_window(core);
	else if (key == W)
		core->move.up = 1;
	else if (key == S)
		core->move.down = 1;
	else if (key == E)
		core->move.right = 1;
	else if (key == D)
		core->move.left = 1;
	else if (key == 65361)
		core->move.rotation_l = 1;
	else if (key == 65363)
		core->move.rotation_r = 1;
	return (0);
}

int	release(int key, t_core *core)
{
	if (key == 119)
		core->move.up = 0;
	else if (key == 115)
		core->move.down = 0;
	else if (key == 100)
		core->move.right = 0;
	else if (key == 97)
		core->move.left = 0;
	else if (key == 65361)
		core->move.rotation_l = 0;
	else if (key == 65363)
		core->move.rotation_r = 0;
	return (0);
}
