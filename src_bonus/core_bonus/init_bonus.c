/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:42:27 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/17 18:28:50 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	init_ray(t_ray *ray)
{
	ray->map_pos = ft_collect_mem(1, sizeof(t_vector));
	ray->delta_dist = ft_collect_mem(1, sizeof(t_vector));
	ray->side_dist = ft_collect_mem(1, sizeof(t_vector));
	ray->step = ft_collect_mem(1, sizeof(t_vector));
	ray->wall = ft_collect_mem(1, sizeof(t_wall));
	ray->p_dist = 0;
	ray->hit_side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->perp_wall_dist = 0;
}

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
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	init_player(game->player);
	init_ray(game->ray);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(game->mlx, WIDTH * 0.5, HEIGHT * 0.5);
}
