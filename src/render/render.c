/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:54:12 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/09/14 11:53:22 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	draw_texture_pixel(t_game *game, int x)
{
	int			actual_y;
	int			tex_y;
	uint32_t	color;
	uint8_t		*pixel;
	float		step;

	actual_y = game->ray->draw_start;
	step = (float)game->ray->wall->texture->height
		/ game->ray->line_height;
	tex_y = (int)(actual_y * step);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)game->ray->wall->texture->height)
		tex_y = game->ray->wall->texture->height - 1;
	pixel = &game->ray->wall->texture->pixels[
		(int)(tex_y * game->ray->wall->texture->width
			+ game->ray->wall->pixel->x)
		* game->ray->wall->texture->bytes_per_pixel];
	color = (pixel[0] << 24) | (pixel[1] << 16)
		| (pixel[2] << 8) | pixel[3];
	mlx_put_pixel(game->img, x, game->ray->draw_start, color);
}

static void	calculate_texture_x(t_game *game)
{
	double	wall_x;

	if (game->ray->hit_side == 0)
		wall_x = game->player->pos->y + game->ray->perp_wall_dist
			* game->ray->dir->y;
	else
		wall_x = game->player->pos->x + game->ray->perp_wall_dist
			* game->ray->dir->x;
	wall_x -= floor(wall_x);
	game->ray->wall->pixel->x = (int)(wall_x
			* game->ray->wall->texture->width);
	if ((game->ray->hit_side == 0 && game->ray->dir->x < 0)
		|| (game->ray->hit_side == 1 && game->ray->dir->y < 0))
		game->ray->wall->pixel->x = game->ray->wall->texture->width
			- game->ray->wall->pixel->x - 1;
}

void	select_texture(t_game *game)
{
	if (game->ray->hit_side == 0)
	{
		if (game->ray->dir->x > 0)
			game->ray->wall->texture = game->texture->t_east;
		else
			game->ray->wall->texture = game->texture->t_west;
	}
	else
	{
		if (game->ray->dir->y > 0)
			game->ray->wall->texture = game->texture->t_north;
		else
			game->ray->wall->texture = game->texture->t_south;
	}
}

static void	draw_line(t_game *game, int x)
{
	// int32_t	color;

	select_texture(game);
	calculate_texture_x(game);
	// if (game->ray->hit_side)
	// 	color = 0xFF0000FF; // red
	// else
	// 	color = 0x800000FF; // dark red
	while (game->ray->draw_start < game->ray->draw_end)
	{
		draw_texture_pixel(game, x);
		// mlx_put_pixel(game->img, x, game->ray->draw_start, color);
		game->ray->draw_start++;
	}
}

static void	calculate_height(t_game *game)
{
	if(game->ray->hit_side == 0)
	{
		if (game->ray->dir->x != 0)
			game->ray->perp_wall_dist = (game->ray->wall_map_pos->x - game->player->pos->x + ((1 - game->ray->step->x) / 2)) / game->ray->dir->x;
	}
	else
	{
		if (game->ray->dir->y != 0)
			game->ray->perp_wall_dist = (game->ray->wall_map_pos->y - game->player->pos->y + ((1 - game->ray->step->y) / 2)) / game->ray->dir->y;
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
		if (game->map->map[(int)game->ray->wall_map_pos->y][(int)game->ray->wall_map_pos->x] == '1')
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
	ray->wall = ft_collect_mem(1, sizeof(t_wall));
	ray->wall->pixel = ft_collect_mem(1, sizeof(t_vector));
	ray->wall->texture = ft_collect_mem(1, sizeof(mlx_texture_t));
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
		ray_setup(game, i, game->ray);
		dda_setup(game, game->ray);
		dda_exec(game);
		calculate_height(game);
		draw_line(game, i);
		i++;
	}
}

static void	draw_background(t_game *game)
{
	int			x;
	int			y;
	uint32_t	ceiling_color;
	uint32_t	floor_color;

	ceiling_color = 0x87CEEBFF;
	floor_color = 0x696969FF;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	render(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_background(game);
	raycasting(game);
}
