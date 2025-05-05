/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:07 by joandre           #+#    #+#             */
/*   Updated: 2025/01/16 11:16:44 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	f_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*f_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

char	*f_strjoin(char *s1, char *s2)
{
	char	*start;
	char	*str;

	if (!s1)
		return (NULL);
	str = (char *)malloc((f_strlen(s1) + f_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	start = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (start);
}

void	*f_calloc(unsigned int count, unsigned int size)
{
	void			*pointer;
	unsigned char	*p;
	unsigned int	n;

	pointer = malloc(count * size);
	if (!pointer)
		return (NULL);
	p = pointer;
	n = size * count;
	while (n--)
		*p++ = '\0';
	return (pointer);
}

char	*f_itoa(int n)
{
	char		*str;
	int			i;
	long int	nb;

	nb = n;
	i = 0;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	nb = n;
	str = f_calloc(i + 1, sizeof(char));
	if (!str)
		return (0);
	str[i--] = 0;
	while (nb > 0)
	{
		str[i--] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
