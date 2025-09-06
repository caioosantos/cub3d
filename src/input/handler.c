/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:47:57 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/09/06 13:14:33 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	update_player_position(t_game *game)
{
	t_vector	move_step;
	t_vector	new_pos;

	move_step.x = game->player->velocity->x * game->mlx->delta_time;
	move_step.y = game->player->velocity->y * game->mlx->delta_time;
	new_pos.x = game->player->pos->x + move_step.x;
	new_pos.y = game->player->pos->y + move_step.y;
	game->player->pos->x = new_pos.x;
	game->player->pos->y = new_pos.y;
}

static void	calculate_velocity(t_game *game)
{
	game->player->velocity->x = 0;
	game->player->velocity->y = 0;
	if (game->player->input->up)
	{
		printf("Going up\n");
		game->player->velocity->x += game->player->dir->x
			* game->player->move_speed;
		game->player->velocity->y += game->player->dir->y
			* game->player->move_speed;
	}
	if (game->player->input->down)
	{
		printf("Going down\n");
		game->player->velocity->x -= game->player->dir->x
			* game->player->move_speed;
		game->player->velocity->y -= game->player->dir->y
			* game->player->move_speed;
	}
}

static void	reset_inputs(t_input *input)
{
	input->up = false;
	input->down = false;
	input->left = false;
	input->right = false;
	input->turn_left = false;
	input->turn_right = false;
	input->shoot = false;
}

void	input_hook(void *param)
{
	t_game	*game;
	t_input	*input;

	game = (t_game *)param;
	input = game->player->input;
	reset_inputs(input);
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
	calculate_velocity(game);
	update_player_position(game);
}
