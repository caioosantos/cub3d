/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:31:07 by gyasuhir         #+#    #+#             */
/*   Updated: 2025/09/04 00:31:09 by gyasuhir        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

t_vector	*multiply_vector(t_vector *v, float multi)
{
	t_vector	*res;

	res = ft_collect_mem(1, sizeof(t_vector));
	res->x = v->x * multi;
	res->y = v->y * multi;
	return (res);
}

t_vector	*sum_vectors(t_vector *va, t_vector *vb)
{
	t_vector	*res;

	res = ft_collect_mem(1, sizeof(t_vector));
	res->x = va->x + vb->x;
	res->y = va->y + vb->y;
	return (res);
}

void	rotate_vector(t_vector *v, float rad)
{
	float		old_x;

	old_x = v->x;
	v->x = v->x * cos(rad) - v->y * sin(rad);
	v->y = old_x * sin(rad) + v->y * cos(rad);
}

float	vector_magnitude(t_vector *v)
{
	return (sqrt((v->x * v->x) + (v->y * v->y)));
}

t_vector	*copy_vector(t_vector *v)
{
	t_vector	*res;

	res = ft_collect_mem(1, sizeof(t_vector));
	res->x = v->x;
	res->y = v->y;
	return (res);
}
