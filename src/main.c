/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschroed <mschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:46:42 by mschroed          #+#    #+#             */
/*   Updated: 2019/10/29 16:32:05 by mschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"

void		clean_it(char **spl)
{
	int		i;

	i = 0;
	while (spl[i] != '\0')
	{
		free(spl[i]);
		i++;
	}
	free(spl);
}

void		in_it(t_fdf *fdf, char *name)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, name);
	fdf->vec = make_vector();
	fdf->fc3vec = make_fc3vector();
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->img_meta.addr = mlx_get_data_addr(fdf->img, &fdf->img_meta.bpp,
		&fdf->img_meta.size_line, &fdf->img_meta.endian);
	fdf->img_meta.bpp /= 8;
	fdf->draw = 1;
	fdf->x_rot = 0;
	fdf->y_rot = 0;
	fdf->zoom = 20;
}

void		stuff_it(t_fdf *fdf, t_vector *vec, const int fd, char *line)
{
	float	f;
	int		i;
	int		j;
	int		gnl;
	char	**spl;

	j = 0;
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		spl = ft_strsplit(line, ' ');
		i = 0;
		while (spl[i] != NULL)
		{
			f = ft_atoi(spl[i]);
			append_vector(vec, f * 100.f);
			i++;
		}
		j++;
		clean_it(spl);
		free(line);
	}
	free(line);
	fdf->row_len = j;
	fdf->col_len = i;
}

void		bind_it(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, (t_fptr)(&loop_it), fdf);
	mlx_hook(fdf->win, 2, 0, (t_fptr)(&key_press), fdf);
	mlx_hook(fdf->win, 4, 0, (t_fptr)(&mouse_press), fdf);
	mlx_hook(fdf->win, 5, 0, (t_fptr)(&mouse_release), fdf);
	mlx_hook(fdf->win, 6, 0, (t_fptr)(&mouse_move), fdf);
	mlx_hook(fdf->win, 17, 0, (t_fptr)(&x_close), fdf);
}

int			main(int argc, char **argv)
{
	t_fdf	fdf;
	int		fd;
	char	*line;

	line = NULL;
	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (0);
		in_it(&fdf, argv[1]);
		stuff_it(&fdf, fdf.vec, fd, line);
		bind_it(&fdf);
		mlx_loop(fdf.mlx);
	}
	return (0);
}
