/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:54:12 by gyasuhir         #+#    #+#             */
/*   Updated: 2025/09/03 23:54:13 by gyasuhir        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void    dda_setup(t_game *game)
{

}

void    dda_exec(t_game *game)
{

}

void    ray_setup(t_game *game, int i)
{

}

void    calculate_height(t_game *game)
{

}
void    draw_line(t_game *game, int i)
{

}


void    raycasting(t_game *game)
{
    int     i;

    i = 0;
    while (i < WIDTH)
    {
        ray_setup(game, i);
        dda_setup(game);
        dda_exec(game);
        calculate_height(game);
        // identificar a cor da parede baseado no hit_side
        draw_line(game, i);
    }
}

void    generate_frame(t_game *game)
{
    // limpar tela para proxima imagem

    // desenhar ceu e chao na imagem
    
    raycasting(game); // desenhar pareder com raycasting

}

void    render(t_game *game)
{
    generate_frame(game);
    draw_frame(game);
}