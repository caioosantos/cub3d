/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:07:18 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/12 21:09:32 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	read_file(t_game *game, int fd)
{
	char	*line;
	char	*temp;
	char	*joined;

	line = ft_strdup("");
	while (42)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		joined = ft_strjoin(line, temp);
		untrack_pointer(temp);
		untrack_pointer(line);
		line = joined;
	}
	close(fd);
	game->map->content = ft_split(line, '\n');
	untrack_pointer(line);
}

void	validate_file(t_game *game, char *file)
{
	char	*ext;
	int		fd;

	ext = ft_strrchr(file, '.');
	if (!ext)
		destroy_game(game, EXTENSION);
	if (ft_strncmp(ext, ".cub", 4) != 0)
		destroy_game(game, EXTENSION);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		destroy_game(game, FILE);
	read_file(game, fd);
}

void	parse(t_game *game, char *file)
{
	int	i;

	i = 0;
	validate_file(game, file);
	get_texture_and_color(game, game->map->content, &i);
	get_map(game, game->map->content, &i);
	validate_texture(game, game->texture->north_path);
	validate_texture(game, game->texture->south_path);
	validate_texture(game, game->texture->west_path);
	validate_texture(game, game->texture->east_path);
	validate_colors(game);
	validate_map(game, game->map->map);
	validate_player(game);
}
