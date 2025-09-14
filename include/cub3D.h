/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:21:45 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/14 11:59:52 by gyasuhir         ###   ########.fr       */
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

# define WIDTH 1280
# define HEIGHT 720
# define M_PI 3.14159265358979323846

# define EXTENSION "ERROR: Invalid extension"
# define FILE "ERROR: Invalid file"
# define WRONG_ARGUMENTS "ERROR: Wrong number of arguments"
# define TOO_MANY_ARGUMENTS "ERROR: Too many arguments"
# define TOO_MANY_PLAYERS "ERROR: Too many players"
# define MAP_NOT_CLOSED "ERROR: Map not closed"
# define DUPLICATE_TEXTURE "ERROR: Duplicate texture"
# define DUPLICATE_COLOR "ERROR: Duplicate color"
# define INVALID_TEXTURE_PATH "ERROR: Invalid texture path"
# define INVALID_COLOR_PATH "ERROR: Invalid color path"
# define INVALID_MAP "ERROR: Invalid map"
# define INVALID_COLOR "ERROR: Invalid rgb color"
# define INVALID_TEXTURE "ERROR: Invalid texture"
# define INVALID_PLAYER "ERROR: Invalid player"
# define INVALID_CHAR "ERROR: Invalid character"
# define INVALID_START_POSITION "ERROR: Invalid player starting position"
# define ERR_TEXTURE_LOAD "ERROR: Failed to load texture"



typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_wall
{
	int				pixel_x;
	int				pixel_y;
	mlx_texture_t	*texture;
}	t_wall;

typedef struct s_ray
{
	t_vector		*camera_pixel;
	t_vector		*dir;
	t_vector		*map_pos;
	t_vector		*step;
	t_vector		*delta_dist;
	t_vector		*side_dist;
	t_vector		*wall_map_pos;
	float			p_dist;
	int				hit_side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	float			perp_wall_dist;
	t_wall			*wall;
}	t_ray;

typedef struct s_input
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	turn_left;
	bool	turn_right;
	bool	shoot;
}	t_input;


typedef struct s_player
{
	char		start;
	t_vector	*pos;
	t_vector	*dir;
	t_vector	*plane;
	float		plane_multi;
	t_input		*input;
	float		move_speed;
	t_vector	*velocity;
	float		rot_speed;
	int			player;
	t_vector	*strafe_velocity;
}	t_player;

typedef struct s_texture
{
	mlx_texture_t	*t_north;
	mlx_texture_t	*t_south;
	mlx_texture_t	*t_east;
	mlx_texture_t	*t_west;
	char			*north_path;
	char			*south_path;
	char			*east_path;
	char			*west_path;
	char			*floor_color;
	char			*ceiling_color;
	int				north;
	int				south;
	int				east;
	int				west;
	int				floor;
	int				ceiling;
}	t_texture;

typedef struct s_map
{
	char	**map;
	char	**content;
	int		height;
}	t_map;

typedef struct s_game
{
	t_map		*map;
	t_player	*player;
	mlx_t		*mlx;
	t_texture	*texture;
	t_ray		*ray;
	mlx_image_t	*img;
}	t_game;

// init
void		init(t_game *game);

// parse
void		parse(t_game *game, char *file);
void		get_texture_and_color(t_game *game, char **content, int *i);
void		get_map(t_game *game, char **map, int *i);
void		validate_texture(t_game *game, char *path);

int			startwith(char *content, char *start);
int			is_valid_line(char *content);
int			only_spaces(char *content);
int			contains_any_char(char *str, char *chars);
int			count_map(t_game *game, char **map, int i);

void		validate_colors(t_game *game);
void		validate_map(t_game *game, char **map);
void		get_player(t_game *game, char **map, int i, int j);
void		validate_player(t_game *game);

void		set_start_position(t_player *player, char pos);

// input
void		input_hook(void *param);

// render
void		render(void *param);
void		load_textures(t_game *game);

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

/**
 * Rotates a 2D vector by a given angle in radians.
 *
 * @param v   Pointer to the vector to be rotated. The vector is modified in place.
 * @param rad Angle in radians by which to rotate the vector.
 */
void		rotate_vector(t_vector *v, float rad);

// utils
void		print_error(char *msg);
void		destroy_game(t_game *game, char *msg);

#endif
