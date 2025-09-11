/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_start_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:53:48 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/11 12:55:37 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	set_north(t_player *player)
{
	player->dir->x = 0;
	player->dir->y = -1;
	player->plane->x = 0.66;
	player->plane->y = 0;
}

static void	set_south(t_player *player)
{
	player->dir->x = 0;
	player->dir->y = 1;
	player->plane->x = -0.66;
	player->plane->y = 0;
}

static void	set_west(t_player *player)
{
	player->dir->x = -1;
	player->dir->y = 0;
	player->plane->x = 0;
	player->plane->y = 0.66;
}

static void	set_east(t_player *player)
{
	player->dir->x = 1;
	player->dir->y = 0;
	player->plane->x = 0;
	player->plane->y = -0.66;
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
