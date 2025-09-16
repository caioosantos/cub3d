/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:22:42 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/15 20:41:43 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	calculate_height(t_game *game)
{
	if (game->ray->hit_side == 0)
	{
		if (game->ray->dir->x != 0)
			game->ray->perp_wall_dist = (game->ray->wall_map_pos->x \
				- game->player->pos->x + ((1 - game->ray->step->x) / 2)) \
				/ game->ray->dir->x;
	}
	else
	{
		if (game->ray->dir->y != 0)
			game->ray->perp_wall_dist = (game->ray->wall_map_pos->y \
				- game->player->pos->y + ((1 - game->ray->step->y) / 2)) \
				/ game->ray->dir->y;
	}
	if (game->ray->perp_wall_dist > 0)
		game->ray->line_height = (int)(HEIGHT / game->ray->perp_wall_dist);
	else
		game->ray->line_height = HEIGHT;
	game->ray->draw_start = HEIGHT / 2 - game->ray->line_height / 2;
	if (game->ray->draw_start < 0)
		game->ray->draw_start = 0;
	game->ray->draw_end = HEIGHT / 2 + game->ray->line_height / 2;
	if (game->ray->draw_end >= HEIGHT)
		game->ray->draw_end = HEIGHT - 1;
	return ;
}
