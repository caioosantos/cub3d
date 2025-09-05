/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:54:12 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/09/04 18:53:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	ray_setup(t_game *game, int i)
{
	game->ray->camera_pixel.x = 2 * i / (double)WIDTH - 1;
	game->ray->dir.x = game->player->dir->x + game->player->camera_plane->x
		* game->ray->camera_pixel.x;
	game->ray->dir.y = game->player->dir->y + game->player->camera_plane->y
		* game->ray->camera_pixel.x;
	game->ray->map_pos.x = (int)game->player->pos->x;
	game->ray->map_pos.y = (int)game->player->pos->y;
	game->ray->delta_dist.x = fabsf(1 / game->ray->dir.x);
	game->ray->delta_dist.y = fabsf(1 / game->ray->dir.y);
}

static void	dda_setup(t_game *game)
{
	if (game->ray->dir.x < 0)
	{
		game->ray->step.x = -1;
		game->ray->side_dist.x = (game->player->pos->x - game->ray->map_pos.x)
			* game->ray->delta_dist.x;
	}
	else
	{
		game->ray->step.x = 1;
		game->ray->side_dist.x = (game->ray->map_pos.x + 1.0
				- game->player->pos->x) * game->ray->delta_dist.x;
	}
	if (game->ray->dir.y < 0)
	{
		game->ray->step.y = -1;
		game->ray->side_dist.y = (game->player->pos->y - game->ray->map_pos.y)
			* game->ray->delta_dist.y;
	}
	else
	{
		game->ray->step.y = 1;
		game->ray->side_dist.y = (game->ray->map_pos.y + 1.0
				- game->player->pos->y) * game->ray->delta_dist.y;
	}
}

static void	dda_exec(t_game *game)
{
	while (1)
	{
		if (game->ray->side_dist.x < game->ray->side_dist.y)
		{
			game->ray->side_dist.x += game->ray->delta_dist.x;
			game->ray->map_pos.x += game->ray->step.x;
			game->ray->hit_side = 0;
		}
		else
		{
			game->ray->side_dist.y += game->ray->delta_dist.y;
			game->ray->map_pos.y += game->ray->step.y;
			game->ray->hit_side = 1;
		}
		if (game->map->map[game->ray->map_pos.y][game->ray->map_pos.x] == '1')
			break ;
	}
}

static void	calculate_height(t_game *game)
{
	if (game->ray->hit_side == 0)
		game->ray->p_dist = (game->ray->side_dist.x - game->ray->delta_dist.x);
	else
		game->ray->p_dist = (game->ray->side_dist.y - game->ray->delta_dist.y);
	game->ray->line_height = (int)(HEIGHT / game->ray->p_dist);
	game->ray->draw_start = -game->ray->line_height / 2 + HEIGHT / 2;
	if (game->ray->draw_start < 0)
		game->ray->draw_start = 0;
	game->ray->draw_end = game->ray->line_height / 2 + HEIGHT / 2;
	if (game->ray->draw_end >= HEIGHT)
		game->ray->draw_end = HEIGHT - 1;
}
static void	draw_line(t_game *game, int i)
{
	int	y;
	int	color;

	y = 0;
	if (game->ray->hit_side == 1)
		color = 0x00FF00FF;
	else
		color = 0x00FFFFFF;
	while (y < game->ray->draw_start)
	{
		mlx_put_pixel(game->img, i, y, 0x000000FF);
		y++;
	}
	while (y < game->ray->draw_end)
	{
		mlx_put_pixel(game->img, i, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->img, i, y, 0xFF0000FF);
		y++;
	}
}

static void	raycasting(t_game *game)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		ray_setup(game, i);
		dda_setup(game);
		dda_exec(game);
		calculate_height(game);
		draw_line(game, i);
		i++;
	}
}

void	generate_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	raycasting(game);
}
