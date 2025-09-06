/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:20:44 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/06 13:08:42 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int ac, char **av)
{
	t_game	*game;

	(void)av;
	if (ac != 2)
	{
		printf("ERROR: wrong number of arguments\n");
		exit(EXIT_FAILURE);
	}
	game = ft_collect_mem(1, sizeof(t_game));
	if (!game)
		return (0);
	init(game);
	parse(game, av[1]);
	mlx_loop_hook(game->mlx, &render, game);
	mlx_loop_hook(game->mlx, &input_hook, game);
	mlx_loop(game->mlx);
	if (game->mlx)
		destroy_game(game);
	return (0);
}
