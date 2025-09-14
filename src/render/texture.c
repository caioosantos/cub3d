/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:58:07 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/09/14 11:02:30 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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