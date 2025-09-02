/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:35:17 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/02 19:23:20 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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

int	is_valid_line(char *content)
{
	int	i;

	if (!content)
		return (0);
	i = 0;
	while (content[i])
	{
		if (!ft_strchr(" 01NSEW", content[i]))
			return (0);
		i++;
	}
	return (1);
}
