/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:54:12 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/09/05 19:36:02 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// static void	dda_setup(t_game *game)
// {

// }

// static void	dda_exec(t_game *game)
// {

// }

// static void	calculate_height(t_game *game)
// {

// }
// static void	draw_line(t_game *game, int i)
// {

// }

static void	ray_setup(t_game *game, int i, t_ray *ray)
{
	// talvez tirar plane_multi e camera_pixel das structs
	game->player->plane_multi = 2 * (i / WIDTH) - 1;
	ray->camera_pixel = multiply_vector(game->player->plane, game->player->plane_multi);
	ray->dir = sum_vectors(game->player->dir, ray->camera_pixel);

}

static void	raycasting(t_game *game)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		game->ray = ft_collect_mem(1, sizeof(t_ray));
		ray_setup(game, i, game->ray);
		// dda_setup(game);
		// dda_exec(game);
		// calculate_height(game);
		// draw_line(game, i);
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
}
