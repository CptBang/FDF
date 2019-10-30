/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschroed <mschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:54:54 by mschroed          #+#    #+#             */
/*   Updated: 2019/10/29 16:42:45 by mschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

# define WIDTH 800
# define HEIGHT 800
# define PI 3.14159265359
# define ABS(x) (x > 0) ? (x) : (-x)

typedef int	(*t_fptr)(void);

enum
{
	escape = 53,
	i = 34,
	zoom_in = 126,
	zoom_out = 125
};

typedef struct	s_c
{
	int x;
	int y;
}				t_c;

typedef struct	s_fc
{
	float x;
	float y;
}				t_fc;

typedef struct	s_fc3
{
	float x;
	float y;
	float z;
}				t_fc3;

typedef struct	s_img_meta
{
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img_meta;

typedef struct	s_vector
{
	size_t		cap;
	size_t		len;
	float		*arr;
}				t_vector;

typedef struct	s_fc3vector
{
	size_t		cap;
	size_t		len;
	t_fc3		*arr;
}				t_fc3vector;

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	void		*img;
	t_img_meta	img_meta;
	t_vector	*vec;
	t_fc3vector	*fc3vec;
	int			row_len;
	int			col_len;
	int			draw;
	int			clicked;
	t_c			prev_mouse;
	float		x_rot;
	float		y_rot;
	float		zoom;
}				t_fdf;

void			expand_vector(t_vector *vector);
t_vector		*append_vector(t_vector *vector, float f);
t_vector		*make_vector(void);
void			clear_vector(t_vector *vector);
void			del_vector(t_vector **vector);

void			expand_fc3vector(t_fc3vector *vector);
t_fc3vector		*append_fc3vector(t_fc3vector *vector, t_fc3 f);
t_fc3vector		*make_fc3vector(void);
void			clear_fc3vector(t_fc3vector *vector);
void			del_fc3vector(t_fc3vector **vector);

void			loop_it(t_fdf *fdf);
void			draw_it(t_fdf *fdf);

void			key_press(int keycode, t_fdf *fdf);
void			mouse_press(int button, int x, int y, t_fdf *fdf);
void			mouse_release(int button, int x, int y, t_fdf *fdf);
void			mouse_move(int x, int y, t_fdf *fdf);
void			x_close(t_fdf *fdf);

int				g_a;

#endif
