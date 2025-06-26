/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:07:38 by jsoares           #+#    #+#             */
/*   Updated: 2025/06/26 14:11:42 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cub3D.h"

int	has_duplicate(char **map, int size, char *word, int start)
{
	char	*other_word;
	int		j;

	j = start + 1;
	while (j < size && map[j])
	{
		other_word = first_word(map[j]);
		if (!other_word)
			return (1); // erro, trate como duplicata para segurança
		if (!ft_strcmp(word, other_word))
		{
			free(other_word);
			return (1);
		}
		free(other_word);
		j++;
	}
	return (0);
}

// Função principal, agora mais limpa
int	texture_dup(char **map, int size)
{
	int		i;
	char	*word;

	i = 0;
	while (i < size && map[i])
	{
		word = first_word(map[i]);
		if (!word)
			return (0);
		if (has_duplicate(map, size, word, i))
		{
			free(word);
			return (0);
		}
		free(word);
		i++;
	}
	return (1);
}
