/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:58:07 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/09/15 20:17:21 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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
			game->ray->wall->texture = game->texture->t_south;
		else
			game->ray->wall->texture = game->texture->t_north;
	}
}

void	calculate_texture_x(t_game *game)
{
	double	wall_x;

	if (game->ray->hit_side == 0)
		wall_x = game->player->pos->y + game->ray->perp_wall_dist
			* game->ray->dir->y;
	else
		wall_x = game->player->pos->x + game->ray->perp_wall_dist
			* game->ray->dir->x;
	wall_x -= floor(wall_x);
	game->ray->wall->pixel_x = (int)(wall_x
			* game->ray->wall->texture->width);
	if ((game->ray->hit_side == 0 && game->ray->dir->x < 0)
		|| (game->ray->hit_side == 1 && game->ray->dir->y < 0))
		game->ray->wall->pixel_x = game->ray->wall->texture->width
			- game->ray->wall->pixel_x - 1;
}

uint32_t	parse_rgb_colors(t_game *game, char *colors)
{
	char	**rgb_colors;
	int		r;
	int		g;
	int		b;

	if (!colors)
		destroy_game(game, INVALID_CHAR);
	rgb_colors = ft_split(colors, ',');
	if (!rgb_colors)
		destroy_game(game, INVALID_COLOR);
	r = (int)ft_atol(rgb_colors[0]);
	g = (int)ft_atol(rgb_colors[1]);
	b = (int)ft_atol(rgb_colors[2]);
	ft_free_matrix(rgb_colors);
	return (get_rgba(r, g, b, 255));
}

void	load_colors(t_game *game)
{
	if (game->texture->ceiling_color)
		game->texture->ceiling_hex
			= parse_rgb_colors(game, game->texture->ceiling_color);
	if (game->texture->floor_color)
		game->texture->floor_hex
			= parse_rgb_colors(game, game->texture->floor_color);
}

void	load_textures(t_game *game)
{
	game->texture->t_north = mlx_load_png(game->texture->north_path);
	game->texture->t_south = mlx_load_png(game->texture->south_path);
	game->texture->t_west = mlx_load_png(game->texture->west_path);
	game->texture->t_east = mlx_load_png(game->texture->east_path);
	if (!game->texture->t_north || !game->texture->t_south
		|| !game->texture->t_west || !game->texture->t_east)
		destroy_game(game, ERR_TEXTURE_LOAD);
}
