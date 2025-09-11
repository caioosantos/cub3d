/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:08:12 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/11 12:53:26 by gyasuhir         ###   ########.fr       */
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
	if (!check_player(map, i, j))
	{
		printf("ERROR: posição do player inválido ou não encontrado!\n");
		exit(EXIT_FAILURE);
	}
	game->player->start = map[i][j];
	game->player->pos->x = i;
	game->player->pos->y = j;
	game->player->player++;
	set_start_position(game->player, map[i][j]);
}

void	validate_player(t_game *game)
{
	if (game->player->player != 1)
	{
		printf("ERROR: Número de jogadores inválido\n");
		exit(EXIT_FAILURE);
	}
}
