/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschroed <mschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:56:34 by mschroed          #+#    #+#             */
/*   Updated: 2019/10/29 16:30:57 by mschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		locate_it(t_fdf *fdf, t_vector *vec)
{
	int		i;
	int		j;
	float	z;

	clear_fc3vector(fdf->fc3vec);
	j = 0;
	while (j < fdf->row_len)
	{
		i = 0;
		while (i < fdf->col_len)
		{
			z = vec->arr[i + j * fdf->col_len];
			append_fc3vector(fdf->fc3vec,
				(t_fc3){(i - (fdf->col_len - 1) / 2.f) * fdf->zoom,
				(j - (fdf->row_len - 1) / 2.f) * fdf->zoom,
					-z * fdf->zoom / 20.f});
			i++;
		}
		j++;
	}
}

void		center_it(t_fdf *fdf, t_fc3vector *vec)
{
	int		i;
	int		j;
	t_fc3	*curr;

	j = 0;
	while (j < fdf->row_len)
	{
		i = 0;
		while (i < fdf->col_len)
		{
			curr = &vec->arr[i + j * fdf->col_len];
			curr->x += WIDTH / 2.f;
			curr->y += HEIGHT / 2.f;
			i++;
		}
		j++;
	}
}

void		spin_x_it(t_fdf *fdf, t_fc3vector *vec, float angle)
{
	int		i;
	int		j;
	t_fc3	*curr;
	t_fc3	calc;

	j = 0;
	while (j < fdf->row_len)
	{
		i = 0;
		while (i < fdf->col_len)
		{
			curr = &vec->arr[i + j * fdf->col_len];
			calc.x = curr->x;
			calc.y = curr->y * cos(angle) + curr->z * sin(angle);
			calc.z = -curr->y * sin(angle) + curr->z * cos(angle);
			*curr = calc;
			i++;
		}
		j++;
	}
}

void		spin_y_it(t_fdf *fdf, t_fc3vector *vec, float angle)
{
	int		i;
	int		j;
	t_fc3	*curr;
	t_fc3	calc;

	j = 0;
	while (j < fdf->row_len)
	{
		i = 0;
		while (i < fdf->col_len)
		{
			curr = &vec->arr[i + j * fdf->col_len];
			calc.x = curr->x * cos(angle) + curr->z * sin(angle);
			calc.y = curr->y;
			calc.z = -curr->x * sin(angle) + curr->z * cos(angle);
			*curr = calc;
			i++;
		}
		j++;
	}
}

void		loop_it(t_fdf *fdf)
{
	if (fdf->draw)
	{
		mlx_clear_window(fdf->mlx, fdf->win);
		ft_bzero(fdf->img_meta.addr, fdf->img_meta.bpp * WIDTH * HEIGHT);
		locate_it(fdf, fdf->vec);
		spin_x_it(fdf, fdf->fc3vec, fdf->x_rot);
		spin_y_it(fdf, fdf->fc3vec, fdf->y_rot);
		center_it(fdf, fdf->fc3vec);
		draw_it(fdf);
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
		fdf->draw = 0;
	}
}
