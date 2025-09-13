/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:08:56 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/13 15:18:33 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	delete_texture(t_game *game)
{
	if (game->texture->t_north)
		mlx_delete_texture(game->texture->t_north);
	if (game->texture->t_south)
		mlx_delete_texture(game->texture->t_south);
	if (game->texture->t_west)
		mlx_delete_texture(game->texture->t_west);
	if (game->texture->t_east)
		mlx_delete_texture(game->texture->t_east);
}

void	print_error(char *msg)
{
	int	size;

	size = ft_strlen(msg);
	if (ft_strncmp(msg, EXTENSION, size))
		ft_putendl_fd(EXTENSION, 2);
	else if (ft_strncmp(msg, FILE, size))
		ft_putendl_fd(FILE, 2);
	else if (ft_strncmp(msg, WRONG_ARGUMENTS, size))
		ft_putendl_fd(WRONG_ARGUMENTS, 2);
	else if (ft_strncmp(msg, TOO_MANY_ARGUMENTS, size))
		ft_putendl_fd(TOO_MANY_ARGUMENTS, 2);
	else if (ft_strncmp(msg, MAP_NOT_CLOSED, size))
		ft_putendl_fd(MAP_NOT_CLOSED, 2);
	else if (ft_strncmp(msg, INVALID_MAP, size))
		ft_putendl_fd(INVALID_MAP, 2);
	else if (ft_strncmp(msg, INVALID_TEXTURE, size))
		ft_putendl_fd(INVALID_TEXTURE, 2);
	else if (ft_strncmp(msg, INVALID_COLOR, size))
		ft_putendl_fd(INVALID_COLOR, 2);
	else if (ft_strncmp(msg, INVALID_PLAYER, size))
		ft_putendl_fd(INVALID_PLAYER, 2);
	else if (ft_strncmp(msg, INVALID_START_POSITION, size))
		ft_putendl_fd(INVALID_START_POSITION, 2);
}

void	destroy_game(t_game *game, char *msg)
{
	if (!game)
		return ;
	if (msg)
		print_error(msg);
	if (game->texture)
		delete_texture(game);
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->mlx)
		mlx_terminate(game->mlx);
	ft_clear_mem();
	exit(EXIT_FAILURE);
}
