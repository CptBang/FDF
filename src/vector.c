/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschroed <mschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:33:16 by mschroed          #+#    #+#             */
/*   Updated: 2019/10/29 14:28:12 by mschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <libft.h>
#include "fdf.h"

void		expand_vector(t_vector *vector)
{
	float	*new_arr;

	vector->cap *= 2;
	new_arr = ft_memalloc(sizeof(float) * vector->cap);
	new_arr = ft_memcpy(new_arr, vector->arr, vector->len * sizeof(float));
	free(vector->arr);
	vector->arr = new_arr;
}

t_vector	*append_vector(t_vector *vector, float f)
{
	while (vector->len >= vector->cap)
		expand_vector(vector);
	vector->arr[vector->len] = f;
	vector->len++;
	return (vector);
}

t_vector	*make_vector(void)
{
	t_vector	*vector;

	vector = ft_memalloc(sizeof(t_vector));
	vector->cap = 16;
	vector->len = 0;
	vector->arr = ft_memalloc(sizeof(float) * vector->cap);
	return (vector);
}

void		clear_vector(t_vector *vector)
{
	vector->len = 0;
}

void		del_vector(t_vector **vector)
{
	if (vector)
	{
		free((*vector)->arr);
		free(*vector);
		*vector = 0;
	}
}
