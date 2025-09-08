/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:37:31 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/08 20:54:56 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	valid_rgb_format(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (color[i] >= '0' && color[i] <= '9')
		{
			i++;
			continue ;
		}
		if (color[i] != ',' && color[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	count_rgb_components(char **colors)
{
	int	count;

	count = 0;
	while (colors[count])
		count++;
	return (count);
}

static int	valid_rgb_numbers(char **colors)
{
	long	nb;
	int		i;

	i = 0;
	while (colors[i])
	{
		nb = ft_atol(colors[i]);
		if (nb < 0 || nb > 255)
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid_colors(char *color)
{
	char	**colors;

	if (!valid_rgb_format(color))
		return (0);
	colors = ft_split(color, ',');
	if (!colors)
		return (0);
	if (count_rgb_components(colors) != 3)
	{
		printf("ERROR: quantidade inválida de componentes RGB!\n");
		ft_free_matrix(colors);
		return (0);
	}
	if (!valid_rgb_numbers(colors))
	{
		printf("ERROR: valor do rgb incorreto!\n");
		ft_free_matrix(colors);
		return (0);
	}
	ft_free_matrix(colors);
	return (1);
}

void	validade_colors(t_game *game)
{
	if (!game->texture->ceiling_color || !game->texture->floor_color)
	{
		printf("ERROR: cores não encontradas!\n");
		exit(EXIT_FAILURE);
	}
	if (!is_valid_colors(game->texture->ceiling_color))
	{
		printf("ERROR: rbg do céu invalido\n");
		exit(EXIT_FAILURE);
	}
	if (!is_valid_colors(game->texture->floor_color))
	{
		printf("ERROR: rbg do chão invalido\n");
		exit(EXIT_FAILURE);
	}
}
