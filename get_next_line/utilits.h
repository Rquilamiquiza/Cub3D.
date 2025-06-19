/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:05:38 by jsoares           #+#    #+#             */
/*   Updated: 2025/06/16 17:50:22 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITS_H
# define UTILITS_H
# include "get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(unsigned int count, unsigned int size);
void	ft_bzero(void *s, unsigned int n);

#endif