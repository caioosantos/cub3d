/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:42:27 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/05 18:21:58 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_player(t_player *player)
{
	// TODO: Pegar posição do jogador a partir do mapa [player->pos]
	// TODO: Pegar direção do jogador a partir do mapa [player->dir]
	player->dir = ft_collect_mem(1, sizeof(t_vector));
	player->plane = ft_collect_mem(1, sizeof(t_vector));
	player->pos = ft_collect_mem(1, sizeof(t_vector));
	player->pos->x = 5;
	player->pos->y = 5;
	player->dir->x = 0;
	player->dir->y = -1;
	player->plane->x = 0.66;
	player->plane->y = 0;
}

void	init(t_game *game)
{
	game->map = ft_collect_mem(1, sizeof(t_map));
	game->player = ft_collect_mem(1, sizeof(t_player));
	game->ray = ft_collect_mem(1, sizeof(t_ray));
	game->mlx = mlx_init(WIDTH, HEIGHT, "Counter-Strike 3", false);
	init_player(game->player);
}
