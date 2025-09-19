/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:47:57 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/09/19 01:51:49 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	mouse_hook(double xpos, double ypos, void *param)
{
	static bool	first_mouse = true;
	t_game		*game;
	float		mouse_sensitivity;

	(void)ypos;
	game = (t_game *)param;
	mouse_sensitivity = 0.003f;
	if (first_mouse)
	{
		first_mouse = false;
		return ;
	}
	if (xpos > WIDTH * 0.5)
	{
		game->player->rot_speed = mouse_sensitivity * (xpos - WIDTH * 0.5);
		rotate_right(game);
	}
	else if (xpos < WIDTH * 0.5)
	{
		game->player->rot_speed = mouse_sensitivity * (WIDTH * 0.5 - xpos);
		rotate_left(game);
	}
	else
		game->player->rot_speed = 0;
	mlx_set_mouse_pos(game->mlx, WIDTH * 0.5, HEIGHT * 0.5);
}

static void	update_player_position(t_game *game)
{
	t_vector	total_velocity;
	t_vector	new_pos;
	t_vector	bias;

	total_velocity.x = (game->player->velocity->x \
		+ game->player->strafe_velocity->x) * game->mlx->delta_time;
	total_velocity.y = (game->player->velocity->y \
		+ game->player->strafe_velocity->y) * game->mlx->delta_time;
	if (total_velocity.x >= 0)
		bias.x = 0.2;
	else
		bias.x = -0.2;
	if (total_velocity.y >= 0)
		bias.y = 0.2;
	else
		bias.y = -0.2;
	new_pos.x = game->player->pos->x + total_velocity.x;
	new_pos.y = game->player->pos->y + total_velocity.y;
	if (game->map->map[(int)(game->player->pos->y)] \
		[(int)(new_pos.x + bias.x)] == '0')
		game->player->pos->x = new_pos.x;
	if (game->map->map[(int)(new_pos.y + bias.y)] \
		[(int)(game->player->pos->x)] == '0')
		game->player->pos->y = new_pos.y;
}

static void	calculate_velocity(t_game *game)
{
	game->player->velocity->x = 0;
	game->player->velocity->y = 0;
	game->player->strafe_velocity->x = 0;
	game->player->strafe_velocity->y = 0;
	if (game->player->input->up)
	{
		game->player->velocity->x += game->player->dir->x
			* game->player->move_speed;
		game->player->velocity->y += game->player->dir->y
			* game->player->move_speed;
	}
	if (game->player->input->down)
	{
		game->player->velocity->x -= game->player->dir->x
			* game->player->move_speed;
		game->player->velocity->y -= game->player->dir->y
			* game->player->move_speed;
	}
	if (game->player->input->left)
		strafe_left(game);
	if (game->player->input->right)
		strafe_right(game);
}

void	calculate_rotation(t_game *game)
{
	if (game->player->input->turn_left)
		rotate_left(game);
	if (game->player->input->turn_right)
		rotate_right(game);
	rotate_vector(game->player->dir, game->player->rot_speed \
		* game->mlx->delta_time);
	rotate_vector(game->player->plane, game->player->rot_speed \
		* game->mlx->delta_time);
	game->player->rot_speed = 0;
}

void	input_hook(void *param)
{
	t_game	*game;
	t_input	*input;

	game = (t_game *)param;
	input = game->player->input;
	reset_inputs(input);
	handler_input(game, input);
	calculate_velocity(game);
	calculate_rotation(game);
	update_player_position(game);
	if (input->interact)
	{
		handle_door(game);
		input->interact = false;
	}
}
