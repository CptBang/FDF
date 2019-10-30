/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc3vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschroed <mschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:33:16 by mschroed          #+#    #+#             */
/*   Updated: 2019/10/29 14:27:44 by mschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <libft.h>
#include "fdf.h"

void		expand_fc3vector(t_fc3vector *fc3vector)
{
	t_fc3	*new_arr;

	fc3vector->cap *= 2;
	new_arr = ft_memalloc(sizeof(t_fc3) * fc3vector->cap);
	new_arr = ft_memcpy(new_arr, fc3vector->arr,
		fc3vector->len * sizeof(t_fc3));
	free(fc3vector->arr);
	fc3vector->arr = new_arr;
}

t_fc3vector	*append_fc3vector(t_fc3vector *fc3vector, t_fc3 fc3)
{
	while (fc3vector->len >= fc3vector->cap)
		expand_fc3vector(fc3vector);
	fc3vector->arr[fc3vector->len] = fc3;
	fc3vector->len++;
	return (fc3vector);
}

t_fc3vector	*make_fc3vector(void)
{
	t_fc3vector	*fc3vector;

	fc3vector = ft_memalloc(sizeof(t_fc3vector));
	fc3vector->cap = 16;
	fc3vector->len = 0;
	fc3vector->arr = ft_memalloc(sizeof(t_fc3) * fc3vector->cap);
	return (fc3vector);
}

void		clear_fc3vector(t_fc3vector *fc3vector)
{
	fc3vector->len = 0;
}

void		del_fc3vector(t_fc3vector **fc3vector)
{
	if (fc3vector)
	{
		free((*fc3vector)->arr);
		free(*fc3vector);
		*fc3vector = 0;
	}
}
