/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschroed <mschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:02:34 by mschroed          #+#    #+#             */
/*   Updated: 2019/10/29 16:37:25 by mschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_press(int keycode, t_fdf *fdf)
{
	if (keycode == escape)
		exit(0);
	else if (keycode == i)
	{
		fdf->x_rot = 0.702421f;
		fdf->y_rot = 0.676575f;
		fdf->draw = 1;
	}
	else if (keycode == zoom_in)
	{
		fdf->zoom *= 2;
		fdf->draw = 1;
	}
	else if (keycode == zoom_out)
	{
		fdf->zoom /= 2;
		if (fdf->zoom < 20 / 1024.f)
			fdf->zoom = 20 / 1024.f;
		fdf->draw = 1;
	}
}

void	x_close(t_fdf *fdf)
{
	(void)fdf;
	exit(0);
}

void	mouse_press(int button, int x, int y, t_fdf *fdf)
{
	(void)button;
	fdf->clicked = 1;
	fdf->prev_mouse = (t_c){x, y};
}

void	mouse_release(int button, int x, int y, t_fdf *fdf)
{
	(void)button;
	(void)x;
	(void)y;
	fdf->clicked = 0;
}

void	mouse_move(int x, int y, t_fdf *fdf)
{
	t_c delta;

	if (fdf->clicked)
	{
		delta = (t_c){fdf->prev_mouse.x - x, fdf->prev_mouse.y - y};
		fdf->x_rot += -delta.y / 50000.f;
		fdf->y_rot += -delta.x / 50000.f;
		fdf->draw = 1;
	}
}
