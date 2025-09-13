/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:08:56 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/12 21:31:37 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	print_error(char *msg)
{
	if (ft_strncmp(msg, EXTENSION, ft_strlen(msg)))
		ft_putendl_fd(EXTENSION, 2);
	else if (ft_strncmp(msg, FILE, ft_strlen(msg)))
		ft_putendl_fd(FILE, 2);
	else if (ft_strncmp(msg, TOO_MANY_ARGUMENTS, ft_strlen(msg)))
		ft_putendl_fd(TOO_MANY_ARGUMENTS, 2);
	else if (ft_strncmp(msg, MAP_NOT_CLOSED, ft_strlen(msg)))
		ft_putendl_fd(MAP_NOT_CLOSED, 2);
	else if (ft_strncmp(msg, INVALID_MAP, ft_strlen(msg)))
		ft_putendl_fd(INVALID_MAP, 2);
	else if (ft_strncmp(msg, INVALID_TEXTURE, ft_strlen(msg)))
		ft_putendl_fd(INVALID_TEXTURE, 2);
	else if (ft_strncmp(msg, INVALID_COLOR, ft_strlen(msg)))
		ft_putendl_fd(INVALID_COLOR, 2);
	else if (ft_strncmp(msg, INVALID_PLAYER, ft_strlen(msg)))
		ft_putendl_fd(INVALID_PLAYER, 2);
	else if (ft_strncmp(msg, INVALID_START_POSITION, ft_strlen(msg)))
		ft_putendl_fd(INVALID_START_POSITION, 2);
}

void	destroy_game(t_game *game, char *msg)
{
	if (!game)
		return ;
	if (msg)
		print_error(msg);
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->mlx)
		mlx_terminate(game->mlx);
	ft_clear_mem();
	exit(EXIT_FAILURE);
}
