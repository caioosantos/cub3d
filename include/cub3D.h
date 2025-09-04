/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:21:45 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/04 00:49:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/mlx_42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH 720
# define HEIGHT 480

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_ray
{
	int			multiplier;
	t_vector	camera_pixel;
	t_vector	dir;
	float		delta_x;
	float		delta_y;
	float		dist_x;
	float		dist_y;
	int			step_x;
	int			step_y;
	t_vector	map_pos;
	int			hit_side;
	int			wall_hit_map_pos;
	float		p_dist;
}	t_ray;

typedef struct s_player
{
	char		start;
	t_point		*pos;
	t_vector	*dir;
	t_vector	*camera_plane;
}	t_player;

typedef struct s_textute
{
	mlx_image_t		*north;
	mlx_image_t		*south;
	mlx_image_t		*east;
	mlx_image_t		*west;
	mlx_texture_t	*t_north;
	mlx_texture_t	*t_south;
	mlx_texture_t	*t_east;
	mlx_texture_t	*t_west;
}	t_textute;

typedef struct s_map
{
	char	**map;
	char	**content;
}	t_map;

typedef struct s_game
{
	t_map		*map;
	t_player	*player;
	mlx_t		*mlx;
	t_ray		*ray;
}	t_game;

// init
void		init(t_game *game);

// parse
void		parse(t_game *game, char *file);

// utils
void		destroy_game(t_game *game);

#endif
