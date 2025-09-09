/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:21:45 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/09 17:03:25 by cbrito-s         ###   ########.fr       */
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

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_player
{
	char		start;
	int			player;
	t_vector	*pos_player;
	t_vector	*dir_player;
	t_vector	*cam_player;
}	t_player;

typedef struct s_image
{
	mlx_image_t		*north;
	mlx_image_t		*south;
	mlx_image_t		*east;
	mlx_image_t		*west;
}	t_image;

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
	t_image		*image;
	t_texture	*texture;
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

void		validade_colors(t_game *game);
void		validate_map(t_game *game, char **map);
void		get_player(t_game *game, char **map, int i, int j);
void		validate_player(t_game *game);

void		set_start_position(t_player *player, char pos);

// utils
void		destroy_game(t_game *game);

#endif
