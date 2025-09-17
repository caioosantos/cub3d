/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:35:17 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/16 19:13:33 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

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

int	startwith(char *content, char *start)
{
	char	*trim;
	int		len;

	if (!content || !start)
		return (0);
	len = ft_strlen(start);
	trim = ft_strtrim(content, " ");
	if (!trim)
		return (0);
	if (ft_strnstr(trim, start, len) && trim[len] == ' ')
	{
		untrack_pointer(trim);
		return (1);
	}
	untrack_pointer(trim);
	return (0);
}

int	is_valid_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (!ft_strchr(" 01NSEWD", line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	contains_any_char(char *str, char *chars)
{
	int	i;
	int	j;

	if (!str || !chars)
		return (0);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (chars[j])
		{
			if (str[i] == chars[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
