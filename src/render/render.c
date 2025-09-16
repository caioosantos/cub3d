/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:54:12 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/09/15 21:48:10 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	draw_line(t_game *game, int x)
{
	int			y;
	int			tex_y;
	float		step;
	float		tex_pos;
	uint8_t		*pixel;

	select_texture(game);
	calculate_texture_x(game);
	step = 1.0f * game->ray->wall->texture->height / game->ray->line_height;
	tex_pos = (game->ray->draw_start - HEIGHT / 2 \
		+ game->ray->line_height / 2) * step;
	y = game->ray->draw_start;
	while (y < game->ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)game->ray->wall->texture->height)
			tex_y = game->ray->wall->texture->height - 1;
		tex_pos += step;
		pixel = &game->ray->wall->texture->pixels[(tex_y \
				* game->ray->wall->texture->width + game->ray->wall->pixel_x)
			* game->ray->wall->texture->bytes_per_pixel];
		mlx_put_pixel(game->img, x, y, get_rgba(pixel[0], pixel[1], \
			pixel[2], pixel[3]));
		y++;
	}
}

static void	ray_setup(t_game *game, int i, t_ray *ray)
{
	game->player->plane_multi = 2 * ((float)i / (float)WIDTH) - 1;
	ray->camera_pixel = multiply_vector(game->player->plane, \
		game->player->plane_multi);
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
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, game->texture->ceiling_hex);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, game->texture->floor_hex);
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
