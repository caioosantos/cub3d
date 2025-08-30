/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:46:02 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/08/30 20:25:38 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	only_spaces(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!ft_isspace(content[i]))
			return (1);
		i++;
	}
	return (0);
}

int	startwith(char *content, char *start)
{
	char	*trim;
	int		len;

	len = ft_strlen(start);
	trim = ft_strtrim(content, ' ');
	if (ft_strnstr(trim, start, len) && trim[len] == ' ')
	{
		untrack_pointer(trim);
		return (0);
	}
	untrack_pointer(trim);
	return (1);
}

void	get_cardinals_and_color(t_game *game, char *content)
{
	if (startwith(content, "NO"))
		game->texture->north++;
	if (startwith(content, "SO"))
		game->texture->south++;
	if (startwith(content, "WE"))
		game->texture->west++;
	if (startwith(content, "EA"))
		game->texture->east++;
	if (startwith(content, "F"))
		game->texture->floor++;
	if (startwith(content, "C"))
		game->texture->ceiling++;
	if (!is_valid_line(content))
	{
		printf("ERROR: caractere inesperado!\n");
		return (1);
	}
	return (0);
}

void	get_textute(t_game *game, char *content)
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
		game->texture->t_north = get_texture_path(content, "NO");

}

int	get_texture_and_color(t_game *game, char **content, int *i)
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
			*i++;
		get_textute(game, content[*i]);
		*i++;
	}
	return (i);
}
