/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschroed <mschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:59:09 by mschroed          #+#    #+#             */
/*   Updated: 2019/10/29 14:33:15 by mschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pixel_put(t_fdf *fdf, t_c p, unsigned int color)
{
	if (p.x < 0 || p.y < 0 || p.x >= WIDTH || p.y >= HEIGHT)
		return ;
	*(int *)(fdf->img_meta.addr + (p.x + p.y * WIDTH)
		* fdf->img_meta.bpp) = color;
}

void	draw_line(t_fdf *fdf, t_fc3 start, t_fc3 end)
{
	const t_fc	d = {end.x - start.x, end.y - start.y};
	const int	steps = fabs(d.x) > fabs(d.y) ? fabs(d.x) : fabs(d.y);
	const t_fc	inc = {d.x / (float)steps, d.y / (float)steps};
	int			i;
	t_fc		curr;

	i = 0;
	curr.x = start.x;
	curr.y = start.y;
	while (i <= steps)
	{
		img_pixel_put(fdf, (t_c){curr.x, curr.y}, 0xFF00FF);
		curr.x += inc.x;
		curr.y += inc.y;
		i++;
	}
}

void	draw_it(t_fdf *fdf)
{
	int		i;
	int		j;

	j = 0;
	while (j < fdf->row_len)
	{
		i = 0;
		while (i < fdf->col_len)
		{
			if (i + 1 < fdf->col_len)
				draw_line(fdf, fdf->fc3vec->arr[i + j * fdf->col_len],
					fdf->fc3vec->arr[i + 1 + j * fdf->col_len]);
			if (j + 1 < fdf->row_len)
				draw_line(fdf, fdf->fc3vec->arr[i + j * fdf->col_len],
					fdf->fc3vec->arr[i + (j + 1) * fdf->col_len]);
			i++;
		}
		j++;
	}
}
