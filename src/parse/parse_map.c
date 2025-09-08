/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:05:36 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/08 17:32:32 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	count_map(t_game *game, char **map, int i)
{
	int	count;

	(void)game;
	count = 0;
	while (map[i])
	{
		if (ft_special_char(map[i]))
			exit(EXIT_FAILURE);
		count++;
		i++;
	}
	return (count);
}

void	get_map(t_game *game, char **map, int *i)
{
	int		len;
	int		j;
	int		map_started;
	int		map_ended;

	len = count_map(game, map, *i);
	game->map->map = ft_collect_mem(len + 1, sizeof(char *));
	if (!game->map->map)
		exit(EXIT_FAILURE);
	j = 0;
	map_started = 0;
	map_ended = 0;
	while (map[*i])
	{
		if (contains_any_char(map[*i], "01NSWE"))
			map_started = 1;
		else if (map_started && only_spaces(map[*i]))
			map_ended = 1;
		if (map_ended && contains_any_char(map[*i], "01NSWE"))
		{
			printf("ERROR: mapa fragmentado!\n");
			exit(EXIT_FAILURE);
		}
		game->map->map[j++] = ft_strdup(map[*i]);
		(*i)++;
	}
	game->map->map[j] = NULL;
	game->map->height = j;
}

int	valid_zero(char **map, int i, int j)
{
	if (i == 0 || j == 0)
		return (0);
	if (!map[i - 1])
		return (0);
	if (!map[i + 1])
		return (0);
	if (j >= (int)ft_strlen(map[i - 1]) || map[i - 1][j] == ' ')
		return (0);
	if (j >= (int)ft_strlen(map[i + 1]) || map[i + 1][j] == ' ')
		return (0);
	if (map[i][j - 1] == ' ')
		return (0);
	if (!map[i][j + 1] || map[i][j + 1] == ' ')
		return (0);
	return (1);
}

void	validate_map(t_game *game, char **map)
{
	int	i;
	int	j;

	if (!map || !*map)
	{
		printf("ERROR: Não foi possível encontrar o mapa!\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(" 01NSWE", map[i][j]))
			{
				printf("ERROR: %d\n", map[i][j]);
				exit(EXIT_FAILURE);
			}
			if (map[i][j] == '0')
				if (!valid_zero(map, i, j))
				{
					printf("ERROR: '0' em posição inválida no mapa!\n");
					exit(EXIT_FAILURE);
				}
			if (ft_strchr("NSWE", map[i][j]))
				get_player(game, map, i, j);
			j++;
		}
		i++;
	}
}
