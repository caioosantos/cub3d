/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:54:12 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/09/06 10:29:39 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	draw_line(t_game *game, int i)
{
	int32_t	color;

	if (game->ray->hit_side)
		color = 0xFF0000FF; // red
	else
		color = 0x800000FF; // dark red
	while (game->ray->draw_start < game->ray->draw_end)
	{
		mlx_put_pixel(game->img, i, game->ray->draw_start, color);
		game->ray->draw_start++;
	}
}

static void	calculate_height(t_game *game)
{
	float	perp_wall_dist;

	perp_wall_dist = 0;
	if(game->ray->hit_side == 0)
		perp_wall_dist = (game->ray->wall_map_pos->x - game->player->pos->x + ((1 - game->ray->step->x) / 2)) / game->ray->dir->x;
	else
		perp_wall_dist = (game->ray->wall_map_pos->y - game->player->pos->y + ((1 - game->ray->step->y) / 2)) / game->ray->dir->y;
	game->ray->line_height = HEIGHT / perp_wall_dist;
	game->ray->draw_start = HEIGHT / 2 - game->ray->line_height / 2;
	game->ray->draw_end = HEIGHT / 2 + game->ray->line_height / 2;
	
	return ;
}

static void	dda_exec(t_game *game)
{
	bool		hit;
	float		dda_size_x;
	float		dda_size_y;

	dda_size_x = game->ray->side_dist->x;
	dda_size_y = game->ray->side_dist->y;
	hit = false;
	game->ray->wall_map_pos = copy_vector(game->ray->map_pos);
	while (hit == false)
	{
		if (dda_size_x < dda_size_y)
		{
			game->ray->wall_map_pos->x += game->ray->step->x;
			dda_size_x += game->ray->delta_dist->x;
			game->ray->hit_side = 0;
		}
		else
		{
			game->ray->wall_map_pos->y += game->ray->step->y;
			dda_size_y += game->ray->delta_dist->y;
			game->ray->hit_side = 1;
		}
		if (game->map->content[(int)game->ray->wall_map_pos->y][(int)game->ray->wall_map_pos->x] > '0')
			hit = true;
	}
}

static void	dda_setup(t_game *game, t_ray *ray)
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
	if (ray->dir->x < 0)
	{
		ray->side_dist->x = (game->player->pos->x - ray->map_pos->x) * ray->delta_dist->x;
		ray->step->x = -1;
	}
	else
	{
		ray->side_dist->x = (ray->map_pos->x + 1.0 - game->player->pos->x) * ray->delta_dist->x;
		ray->step->x = 1;
	}
	if (ray->dir->y < 0)
	{
		ray->side_dist->y = (game->player->pos->y - ray->map_pos->y) * ray->delta_dist->y;
		ray->step->y = -1;
	}
	else
	{
		ray->side_dist->y = (ray->map_pos->y + 1.0 - game->player->pos->y) * ray->delta_dist->y;
		ray->step->y = 1;
	}

}

static void	ray_setup(t_game *game, int i, t_ray *ray)
{
	ray->map_pos = ft_collect_mem(1, sizeof(t_vector));
	game->player->plane_multi = 2 * ((float)i / (float)WIDTH) - 1;
	ray->camera_pixel = multiply_vector(game->player->plane, game->player->plane_multi);
	ray->dir = sum_vectors(game->player->dir, ray->camera_pixel);
	ray->map_pos->x = floor(game->player->pos->x);
	ray->map_pos->y = floor(game->player->pos->y);
}

static void	raycasting(t_game *game)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		game->ray = ft_collect_mem(1, sizeof(t_ray));
		ray_setup(game, i, game->ray);
		dda_setup(game, game->ray);
		dda_exec(game);
		calculate_height(game);
		draw_line(game, i);
		i++;
	}
}

void	render(t_game *game)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%c", game->map->content[i][j]);
		}
		printf("\n");
	}
	// TODO background(game);
	raycasting(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}
