/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:47:57 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/09/06 12:42:48 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	walk_up(t_game *game)
{
	game->player->velocity->x = game->player->dir->x;
	game->player->velocity->y = game->player->dir->y;
	game->player->velocity = multiply_vector(game->player->velocity, game->player->move_speed);
}

void	walk_down(t_game *game)
{
	game->player->velocity->x = game->player->dir->x;
	game->player->velocity->y = game->player->dir->y;
	game->player->velocity = multiply_vector(game->player->velocity, -game->player->move_speed);
}

void	stop_walking(t_game *game)
{
	multiply_vector(game->player->velocity, 0.0);
}

void	update_input(t_game *game)
{
	t_vector *new_pos;

	new_pos = multiply_vector(game->player->velocity, game->mlx->delta_time);
	game->player->pos->x += new_pos->x;
	game->player->pos->y += new_pos->y;
	free(new_pos);
}

void	check_input(t_game *game)
{
	if (game->player->input->up)
		walk_up(game);
	else if (game->player->input->down)
		walk_down(game);
	else
		stop_walking(game);
	update_input(game);
}

void	input_hook(void *param)
{
	t_game	*game;
	t_input	*input;

	game = (t_game *)param;
	input = game->player->input;
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
	check_input(game);
}