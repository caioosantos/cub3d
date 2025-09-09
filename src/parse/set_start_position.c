/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_start_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:53:48 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/09 17:51:27 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	set_north(t_player *player)
{
	player->dir_player->x = 0;
	player->dir_player->y = -1;
	player->cam_player->x = 0.66;
	player->cam_player->y = 0;
}

static void	set_south(t_player *player)
{
	player->dir_player->x = 0;
	player->dir_player->y = 1;
	player->cam_player->x = -0.66;
	player->cam_player->y = 0;
}

static void	set_west(t_player *player)
{
	player->dir_player->x = -1;
	player->dir_player->y = 0;
	player->cam_player->x = 0;
	player->cam_player->y = 0.66;
}

static void	set_east(t_player *player)
{
	player->dir_player->x = 1;
	player->dir_player->y = 0;
	player->cam_player->x = 0;
	player->cam_player->y = -0.66;
}

void	set_start_position(t_player *player, char pos)
{
	if (pos == 'N')
		set_north(player);
	else if (pos == 'S')
		set_south(player);
	else if (pos == 'W')
		set_west(player);
	else if (pos == 'E')
		set_east(player);
}
