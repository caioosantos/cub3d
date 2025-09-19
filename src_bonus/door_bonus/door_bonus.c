/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:54:20 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/19 02:00:00 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"
#include <math.h>

/* retorna 1 e preenche out_x/out_y se houver porta ('D' ou 'O') 1 tile à frente */
static int find_door_in_front(t_game *game, int *out_x, int *out_y)
{
	float fx;
	float fy;
	int nx;
	int ny;

	if (!game || !game->player || !game->player->pos || !game->player->dir)
		return (0);
	/* 1.0f = distância em tiles para checar; ajuste se quiser maior alcance */
	fx = game->player->pos->x + game->player->dir->x * 1.0f;
	fy = game->player->pos->y + game->player->dir->y * 1.0f;
	nx = (int)floorf(fx);
	ny = (int)floorf(fy);
	if (ny < 0 || nx < 0 || ny >= game->map->height)
		return (0);
	if (!game->map->map[ny])
		return (0);
	if ((int)ft_strlen(game->map->map[ny]) <= nx)
		return (0);
	if (game->map->map[ny][nx] == 'D')
	{
		*out_x = nx;
		*out_y = ny;
		return (1);
	}
	return (0);
}

/* abre porta: marca mapa como passável e desenha overlay com door_1.png */
static void open_door_and_draw_overlay(t_game *game, int x, int y)
{
	mlx_image_t	*img;
	int			px;
	int			py;
	int			tw;
	int			th;

	if (!game || !game->texture || !game->texture->t_door_open)
		return ;
	/* 1) tornar passável no mapa */
	game->map->map[y][x] = '0';
	/* 2) criar imagem da textura de porta aberta */
	img = mlx_texture_to_image(game->mlx, game->texture->t_door_open);
	if (!img)
		return ;
	/* 3) posicionar o overlay alinhado ao tile (usa largura/altura da textura) */
	tw = game->texture->t_door_open->width;
	th = game->texture->t_door_open->height;
	px = x * tw;
	py = y * th;
	/* colocar na janela (overlay) — mantém a imagem visível enquanto o jogo roda */
	mlx_image_to_window(game->mlx, img, px, py);
	/* nota: guardamos img em MLX; se quiser controlar/remover depois, salve o ponteiro */
}

/* pública: chamada após processar inputs (quando player->input->interact == true) */
void handle_door(t_game *game)
{
	int x;
	int y;
	int found;

	if (!game || !game->player || !game->player->input)
		return ;
	if (!game->player->input->interact)
		return ;
	found = find_door_in_front(game, &x, &y);
	if (found)
		open_door_and_draw_overlay(game, x, y);
	/* consumir input */
	game->player->input->interact = false;
}
