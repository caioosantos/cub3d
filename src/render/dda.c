/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:31:54 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/15 20:28:28 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	dda_calculate_dir(t_game *game, t_ray *ray)
{
	if (ray->dir->x < 0)
	{
		ray->side_dist->x = (game->player->pos->x - ray->map_pos->x)
			* ray->delta_dist->x;
		ray->step->x = -1;
	}
	else
	{
		ray->side_dist->x = (ray->map_pos->x + 1.0 - game->player->pos->x)
			* ray->delta_dist->x;
		ray->step->x = 1;
	}
	if (ray->dir->y < 0)
	{
		ray->side_dist->y = (game->player->pos->y - ray->map_pos->y)
			* ray->delta_dist->y;
		ray->step->y = -1;
	}
	else
	{
		ray->side_dist->y = (ray->map_pos->y + 1.0 - game->player->pos->y)
			* ray->delta_dist->y;
		ray->step->y = 1;
	}
}

void	dda_setup(t_game *game, t_ray *ray)
{
	ray->delta_dist = ft_collect_mem(1, sizeof(t_vector));
	ray->side_dist = ft_collect_mem(1, sizeof(t_vector));
	ray->step = ft_collect_mem(1, sizeof(t_vector));
	if (ray->dir->x == 0)
		ray->delta_dist->x = 1e30;
	else
		ray->delta_dist->x = fabs(1 / ray->dir->x);
	if (ray->dir->y == 0)
		ray->delta_dist->y = 1e30;
	else
		ray->delta_dist->y = fabs(1 / ray->dir->y);
	dda_calculate_dir(game, ray);
}

void	dda_exec(t_game *game)
{
	bool		hit;

	hit = false;
	game->ray->wall_map_pos = copy_vector(game->ray->map_pos);
	while (hit == false)
	{
		if (game->ray->side_dist->x < game->ray->side_dist->y)
		{
			game->ray->wall_map_pos->x += game->ray->step->x;
			game->ray->side_dist->x += game->ray->delta_dist->x;
			game->ray->hit_side = 0;
		}
		else
		{
			game->ray->wall_map_pos->y += game->ray->step->y;
			game->ray->side_dist->y += game->ray->delta_dist->y;
			game->ray->hit_side = 1;
		}
		if (game->map->map[(int)game->ray->wall_map_pos->y] \
			[(int)game->ray->wall_map_pos->x] == '1')
			hit = true;
	}
}
