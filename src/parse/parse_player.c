/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:08:12 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/08 17:47:11 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	check_player(char **map, int i, int j)
{
	char	c;

	if (i == 0 || j == 0)
		return (0);
	c = map[i][j];
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (0);
	if (!map[i + 1] || !map[i][j + 1])
		return (0);
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
		|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		return (0);
	return (1);
}

void	get_player(t_game *game, char **map, int i, int j)
{
	(void)game;
	if (!check_player(map, i, j))
	{
		printf("ERROR: posição do player inválido ou não encontrado!\n");
		exit(EXIT_FAILURE);
	}
	game->player->pos_x = i;
	game->player->pos_y = j;
	game->player->player++;
}

void	validate_player(t_game *game)
{
	if (game->player->player != 1)
	{
		printf("ERROR: Número de jogadores inválido\n");
		exit(EXIT_FAILURE);
	}
}
