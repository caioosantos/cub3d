/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:21:45 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/06 10:34:53 by gyasuhir         ###   ########.fr       */
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

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_ray
{
	t_vector	*camera_pixel;
	t_vector	*dir;
	t_vector	*map_pos;
	t_vector	*step;
	t_vector	*delta_dist; // Dist between two x sides or two y sides
	t_vector	*side_dist; // Dist between next x or y side
	t_vector	*wall_map_pos;
	float		p_dist;
	int			hit_side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}	t_ray;

typedef struct s_player
{
	char		start;
	t_vector	*pos;
	t_vector	*dir;
	t_vector	*plane;
	float		plane_multi;
}	t_player;

typedef struct s_texture
{
	mlx_image_t		*north;
	mlx_image_t		*south;
	mlx_image_t		*east;
	mlx_image_t		*west;
	mlx_texture_t	*t_north;
	mlx_texture_t	*t_south;
	mlx_texture_t	*t_east;
	mlx_texture_t	*t_west;
}	t_texture;

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
	mlx_image_t	*img;
}	t_game;

// init
void		init(t_game *game);

// parse
void		parse(t_game *game, char *file);

// render
void		render(t_game *game);

// math
/*
 * Scalar multiplication of a vector involves multiplying each component
 * of the vector by a scalar (a real number). This scales the vector's
 * magnitude and reverses its direction if the scalar is negative.
 *
 * @param v Pointer to the vector to be multiplied.
 * @param multi Scalar value to multiply the vector by.
 * @return Pointer to a new vector containing the result.
 */
t_vector    *multiply_vector(t_vector *v, float multi);

/**
 * Calculates the sum of two integers.
 *
 * @param a The first integer to add.
 * @param b The second integer to add.
 * @return The sum of a and b.
 */
t_vector    *sum_vectors(t_vector *va, t_vector *vb);

/**
 * @brief Calculates the magnitude (length) of a given vector.
 *
 * This function computes the Euclidean norm of the vector pointed to by `vector`.
 *
 * @param v Pointer to a t_vector structure representing the vector.
 * @return The magnitude (float) of the vector.
 */
float	  vector_magnitude(t_vector *v);

/**
 * @brief Creates a copy of the given vector.
 *
 * Allocates memory for a new t_vector and copies the contents of the input vector `v`
 * into the newly allocated vector. The caller is responsible for freeing the returned vector.
 *
 * @param v Pointer to the t_vector to be copied.
 * @return Pointer to the newly allocated copy of the vector, or NULL if allocation fails.
 */
t_vector	*copy_vector(t_vector *v);

// utils
void		destroy_game(t_game *game);

#endif
