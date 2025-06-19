/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:53:47 by justinosoar       #+#    #+#             */
/*   Updated: 2025/06/03 13:48:18 by jsoares          ###   ########.fr       */
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
