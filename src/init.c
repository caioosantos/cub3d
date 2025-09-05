/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:42:27 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/04 00:21:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_data(t_game *game)
{
	game->player->dir->x = 0;
	game->player->dir->y = -1;
	game->player->camera_plane->x = 0.66;
	game->player->camera_plane->y = 0;
}

void	init(t_game *game)
{
	game->map = ft_collect_mem(1, sizeof(t_map));
	game->player = ft_collect_mem(1, sizeof(t_player));
	game->ray = ft_collect_mem(1, sizeof(t_ray));
	game->mlx = mlx_init(WIDTH, HEIGHT, "Counter-Strike 3", false);
	init_data(game);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}
