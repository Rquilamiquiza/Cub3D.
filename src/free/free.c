/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:45:08 by rquilami          #+#    #+#             */
/*   Updated: 2025/06/01 16:19:31 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

void	free_mtx(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}