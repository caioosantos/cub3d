/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:46:02 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/08/29 16:59:40 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	only_spaces(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!ft_isspace(content[i]))
			return (1);
		i++;
	}
	return (0);
}

int	get_texture_and_color(t_game *game, char **content, int *i)
{
	game->texture = ft_collect_mem(1, sizeof(t_texture));
	if (!game->texture)
	{
		printf("ERROR: falha no caminho da textura!\n");
		exit(EXIT_FAILURE);
	}
	while (content[*i])
	{
		if (ft_special_char(content[*i]))
		{
			printf("ERROR: caminho invalido\n");
			exit(EXIT_FAILURE);
		}
		if (only_spaces(content[*i]))
			*i++;
		get_textute(content[*i]);
		*i++;
	}
	return (i);
}
