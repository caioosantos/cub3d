/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:43:56 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/16 20:27:38 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	rotate_left(t_game *game)
{
	if (game->player->start == 'N' || game->player->start == 'S')
		game->player->rot_speed = M_PI * -1;
	else
		game->player->rot_speed = M_PI;
}

void	rotate_right(t_game *game)
{
	if (game->player->start == 'N' || game->player->start == 'S')
		game->player->rot_speed = M_PI;
	else
		game->player->rot_speed = M_PI * -1;
}

void	strafe_left(t_game *game)
{
	game->player->strafe_velocity->x = game->player->dir->x
		* game->player->move_speed;
	game->player->strafe_velocity->y = game->player->dir->y
		* game->player->move_speed;
	if (game->player->start == 'N' || game->player->start == 'S')
		rotate_vector(game->player->strafe_velocity, (M_PI / 2) * -1);
	else
		rotate_vector(game->player->strafe_velocity, M_PI / 2);
}

void	strafe_right(t_game *game)
{
	game->player->strafe_velocity->x = game->player->dir->x
		* game->player->move_speed;
	game->player->strafe_velocity->y = game->player->dir->y
		* game->player->move_speed;
	if (game->player->start == 'N' || game->player->start == 'S')
		rotate_vector(game->player->strafe_velocity, M_PI / 2);
	else
		rotate_vector(game->player->strafe_velocity, (M_PI / 2) * -1);
}

void	reset_inputs(t_input *input)
{
	input->up = false;
	input->down = false;
	input->left = false;
	input->right = false;
	input->turn_left = false;
	input->turn_right = false;
	input->shoot = false;
	input->interact = false;
}
