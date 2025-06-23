/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:53:47 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/23 11:09:07 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	error_msg_fd(char *msg, int fd)
{
	while (*msg)
	{
		ft_putchar_fd(*msg, fd);
		msg++;
	}
	return (1);
}

int	line_between_the_map(t_data *data, int i)
{
	int	k;

	k = i + 1;
	while (data->map_main[k])
	{
		if (ft_isspace(data->map_main[k]))
		{
			if (data->map_main[k][0] != '\n' && data->map_main[k][0] != '\0')
				return (0);
		}
		k++;
	}
	return (1);
}
