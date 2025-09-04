/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:20:44 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/08/28 17:50:39 by cbrito-s         ###   ########.fr       */
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
	render(game);
	mlx_loop(game->mlx);
	if (game->mlx)
		destroy_game(game);
	return (0);
}
