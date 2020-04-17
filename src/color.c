/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 00:42:33 by hdean             #+#    #+#             */
/*   Updated: 2019/12/22 19:42:55 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			count_new_color(int *color, double d, t_color start,
																	t_color end)
{
	t_color		new;

	new.r = start.r + d * (end.r - start.r);
	new.g = start.g + d * (end.g - start.g);
	new.b = start.b + d * (end.b - start.b);
	*color = (new.r << 16) + (new.g << 8) + new.b;
}

int				grad_color(t_int_coord delta, t_point end,
							t_point *current_point, int start)
{
	double	d;
	t_color	start_color;
	t_color	end_color;

	d = 1;
	if (start == end.color)
		return (0);
	if (delta.x != 0 && delta.x > delta.y)
		d = 1 - abs(end.x - current_point->x) / (double)delta.x;
	else if (delta.y != 0 && delta.x <= delta.y)
		d = 1 - abs(end.y - current_point->y) / (double)delta.y;
	start_color = get_rgb_color(start);
	end_color = get_rgb_color(end.color);
	count_new_color(&current_point->color, d, start_color, end_color);
	return (1);
}

static void		change_color(t_mlx *fdf, t_color start, t_color end)
{
	t_dbl_param delta;
	t_dbl_point *dots;
	t_dbl_point *copy_dots;
	t_dbl_param max;
	t_dbl_param min;

	max = max_dbl_dot(fdf->copy_dots);
	min = min_dbl_dot(fdf->copy_dots);
	delta.z = max.z - min.z;
	dots = fdf->dots;
	copy_dots = fdf->copy_dots;
	while (dots)
	{
		if (delta.z == 0)
			dots->color = (start.r << 16) + (start.g << 8) + start.b;
		else
		{
			delta.x = 1 - fabs(max.z - copy_dots->z) / delta.z;
			count_new_color(&dots->color, delta.x, start, end);
		}
		dots = dots->next;
		copy_dots = copy_dots->next;
	}
}

static void		change_color_for_scheme_a(t_mlx *fdf)
{
	if (fdf->color_scheme == 1)
		change_color(fdf, get_rgb_color(ABLUE), get_rgb_color(AWHITE));
	else if (fdf->color_scheme == 2)
		change_color(fdf, get_rgb_color(BLIME), get_rgb_color(BPINK));
	else if (fdf->color_scheme == 3)
		change_color(fdf, get_rgb_color(CRED), get_rgb_color(CSEA));
}

void			color_scheme(t_mlx *fdf, int key)
{
	t_dbl_point *dots;
	t_dbl_point *copy_dots;

	fdf->color_scheme += 1;
	if (fdf->color_scheme == 4)
		fdf->color_scheme = 1;
	if (key == RESET_COLOR)
	{
		dots = fdf->dots;
		copy_dots = fdf->copy_dots;
		while (dots)
		{
			dots->color = copy_dots->color;
			dots = dots->next;
			copy_dots = copy_dots->next;
		}
		fdf->color_scheme = 0;
	}
	else if (key == COLOR_A)
		change_color_for_scheme_a(fdf);
	else if (key == COLOR_B)
		terra_color_scheme(fdf);
	redraw_vectors(fdf);
}
