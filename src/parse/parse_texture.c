/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:46:02 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/03 21:07:25 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	only_spaces(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!ft_isspace(content[i]))
			return (0);
		i++;
	}
	return (1);
}

void	get_cardinals_and_color(t_game *game, char *content)
{
	if (startwith(content, "NO"))
		game->texture->north++;
	else if (startwith(content, "SO"))
		game->texture->south++;
	else if (startwith(content, "WE"))
		game->texture->west++;
	else if (startwith(content, "EA"))
		game->texture->east++;
	else if (startwith(content, "F"))
		game->texture->floor++;
	else if (startwith(content, "C"))
		game->texture->ceiling++;
	else if (!is_valid_line(content))
	{
		printf("ERROR: caractere inesperado!\n");
		exit(EXIT_FAILURE);
	}
}

char	*get_texture_path(char *content, char *start)
{
	char	*path;
	char	*trim;
	int		len;

	len = ft_strlen(start);
	trim = ft_strtrim(content, " ");
	while (trim[len])
	{
		if (trim[len] != ' ')
		{
			path = ft_substr(trim, len, ft_strlen(trim) - len);
			untrack_pointer(trim);
			return (path);
		}
		len++;
	}
	untrack_pointer(trim);
	return (NULL);
}

int	get_textute(t_game *game, char *content)
{
	get_cardinals_and_color(game, content);
	if (game->texture->north > 1 || game->texture->south > 1
		|| game->texture->west > 1 || game->texture->east > 1)
	{
		printf("ERROR: texturas duplicadas!\n");
		exit(EXIT_FAILURE);
	}
	if (game->texture->floor > 1 || game->texture->ceiling > 1)
	{
		printf("ERROR: Cores duplicadas\n");
		exit(EXIT_FAILURE);
	}
	if (startwith(content, "NO"))
		game->texture->north_path = get_texture_path(content, "NO");
	else if (startwith(content, "SO"))
		game->texture->south_path = get_texture_path(content, "SO");
	else if (startwith(content, "WE"))
		game->texture->west_path = get_texture_path(content, "WE");
	else if (startwith(content, "EA"))
		game->texture->east_path = get_texture_path(content, "EA");
	else if (startwith(content, "F"))
		game->texture->floor_color = get_texture_path(content, "F");
	else if (startwith(content, "C"))
		game->texture->ceiling_color = get_texture_path(content, "C");
	else if (!is_valid_line(content))
	{
		printf("ERROR: caractere inesperado!\n");
		return (1);
	}
	return (0);
}

void	get_texture_and_color(t_game *game, char **content, int *i)
{
	game->texture = ft_collect_mem(1, sizeof(t_texture));
	if (!game->texture)
	{
		printf("ERROR: falha no caminho da textura!\n");
		exit(EXIT_FAILURE);
	}
	while (content[*i])
	{
		if (ft_special_char(content[*i]))
		{
			printf("ERROR: caminho invalido\n");
			exit(EXIT_FAILURE);
		}
		if (only_spaces(content[*i]))
		{
			(*i)++;
			continue;
		}
		if (game->texture->north >= 1 && game->texture->south >= 1 &&
			game->texture->west >= 1 && game->texture->east >= 1 &&
			game->texture->floor >= 1 && game->texture->ceiling >= 1)
			break ;
		get_textute(game, content[*i]);
		(*i)++;
	}
	if (!game->texture->north_path || !game->texture->south_path
			|| !game->texture->west_path || !game->texture->east_path)
	{
		printf("ERROR: Textura invalida!\n");
		exit(EXIT_FAILURE);
	}
	if (!game->texture->floor_color || !game->texture->ceiling_color)
	{
		printf("ERROR: Color invalido!\n");
		exit(EXIT_FAILURE);
	}
}

void	validate_texture(t_game *game, char *path)
{
	char	*ext;
	int		fd;

	(void)game;
	ext = ft_strrchr(path, '.');
	if (!ext)
		exit(EXIT_FAILURE);
	if (ft_strncmp(ext, ".png", 4) != 0)
	{
		printf("ERROR: extensão invalida!\n");
		exit(EXIT_FAILURE);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR: caminho da textura invalido!\n");
		exit(EXIT_FAILURE);
	}
	close(fd);
}
