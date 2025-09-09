/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:42:27 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/09 17:52:14 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init(t_game *game)
{
	game->map = ft_collect_mem(1, sizeof(t_map));
	game->player = ft_collect_mem(1, sizeof(t_player));
	game->player->pos_player = ft_collect_mem(1, sizeof(t_vector));
	game->player->dir_player = ft_collect_mem(1, sizeof(t_vector));
	game->player->cam_player = ft_collect_mem(1, sizeof(t_vector));
	game->player->player = 0;
	game->mlx = mlx_init(1200, 800, "Counter-Strike 3", false);
}
