/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:42:27 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/13 15:27:50 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// static void	load_textures(t_game *game)
// {
// 	game->texture->t_north = mlx_load_png(game->texture->north_path);
// 	game->texture->t_south = mlx_load_png(game->texture->south_path);
// 	game->texture->t_west = mlx_load_png(game->texture->west_path);
// 	game->texture->t_east = mlx_load_png(game->texture->east_path);
// 	if (!game->texture->t_north || !game->texture->t_south
// 		|| !game->texture->t_west || !game->texture->t_east)
// 		destroy_game(game);
// }

void	init_player(t_player *player)
{
	player->dir = ft_collect_mem(1, sizeof(t_vector));
	player->plane = ft_collect_mem(1, sizeof(t_vector));
	player->pos = ft_collect_mem(1, sizeof(t_vector));
	player->input = ft_collect_mem(1, sizeof(t_input));
	player->velocity = ft_collect_mem(1, sizeof(t_vector));
	player->strafe_velocity = ft_collect_mem(1, sizeof(t_vector));
	player->move_speed = 5;
	player->velocity->x = 0;
	player->velocity->y = 0;
	player->strafe_velocity->x = 0;
	player->strafe_velocity->y = 0;
	player->rot_speed = 0;
}

void	init(t_game *game)
{
	game->map = ft_collect_mem(1, sizeof(t_map));
	game->player = ft_collect_mem(1, sizeof(t_player));
	game->ray = ft_collect_mem(1, sizeof(t_ray));
	game->mlx = mlx_init(WIDTH, HEIGHT, "Counter-Strike 3", false);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	// load_textures(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	init_player(game->player);
}
