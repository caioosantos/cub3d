/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:20:44 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/15 17:21:49 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
	{
		ft_putendl_fd(WRONG_ARGUMENTS, 2);
		exit(EXIT_FAILURE);
	}
	game = ft_collect_mem(1, sizeof(t_game));
	if (!game)
		return (0);
	init(game);
	parse(game, av[1]);
	load_textures(game);
	load_colors(game);
	mlx_loop_hook(game->mlx, &render, game);
	mlx_loop_hook(game->mlx, &input_hook, game);
	mlx_loop(game->mlx);
	if (game->mlx)
		destroy_game(game, NULL);
	return (0);
}
