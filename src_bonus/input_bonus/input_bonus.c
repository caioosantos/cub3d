/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:17:49 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/17 18:27:43 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	handler_input(t_game *game, t_input *input)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		input->up = true;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		input->down = true;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		input->left = true;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		input->right = true;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		input->turn_left = true;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		input->turn_right = true;
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		input->shoot = true;
	if (mlx_is_key_down(game->mlx, MLX_KEY_E))
		input->interact = true;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
