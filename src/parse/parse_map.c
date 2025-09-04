/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:05:36 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/03 21:06:52 by cbrito-s         ###   ########.fr       */
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

