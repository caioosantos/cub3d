/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:07:18 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/08/29 16:03:26 by cbrito-s         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	if (ft_strncmp(ext, ".cub", 4) != 0)
		exit(EXIT_FAILURE);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	read_file(game, fd);
}

void	parse(t_game *game, char *file)
{
	int	i;

	i = 0;
	validate_file(game, file);
	get_texture_and_color(game, game->map->content, &i);
	get_map(game, file, &i);
	validate_texture(game, game->map->content);
}
