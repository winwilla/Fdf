/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 21:23:55 by hdean             #+#    #+#             */
/*   Updated: 2019/12/20 23:01:33 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		draw_pixel(t_mlx *fdf, t_point pixel)
{
	int		j;
	char	*tmp;

	tmp = fdf->data;
	pixel.x += fdf->center.x;
	pixel.y += fdf->center.y;
	j = pixel.x * 4 + pixel.y * fdf->line_size;
	if (j > (fdf->pic->width * fdf->pic->height *
										fdf->bits_per_pixel / 8 - 1) || j < 0)
		return (0);
	if ((tmp[j] == 0 && tmp[j + 1] == 0 && tmp[j + 2] == 0) ||
								(fdf->z_buffer[pixel.y][pixel.x] < pixel.z))
	{
		fdf->z_buffer[pixel.y][pixel.x] = pixel.z;
		tmp[j] = pixel.color & 0xFF;
		tmp[++j] = (pixel.color >> 8) & 0xFF;
		tmp[++j] = (pixel.color >> 16) & 0xFF;
	}
	return (1);
}

static t_point	double_to_int_point(t_dbl_point *double_point)
{
	t_point int_point;

	int_point.x = round(double_point->x);
	int_point.y = round(double_point->y);
	int_point.z = round(double_point->z);
	int_point.color = double_point->color;
	return (int_point);
}

static void		count_delta_and_sign(t_point start, t_point end,
									t_int_coord *delta, t_int_coord *sign)
{
	delta->x = abs(end.x - start.x);
	delta->y = abs(end.y - start.y);
	sign->x = start.x < end.x ? 1 : -1;
	sign->y = start.y < end.y ? 1 : -1;
}

static void		update_error_and_start(t_point *start, t_int_coord *error,
									t_int_coord delta, t_int_coord sign)
{
	if (error->y > -delta.y)
	{
		error->x -= delta.y;
		start->x += sign.x;
	}
	if (error->y < delta.x)
	{
		error->x += delta.x;
		start->y += sign.y;
	}
}

int				draw_line(t_dbl_point *first_point, t_dbl_point *second_point,
																	t_mlx *fdf)
{
	t_point		start;
	t_point		end;
	t_int_coord	delta;
	t_int_coord	sign;
	t_int_coord	error;

	start = double_to_int_point(first_point);
	end = double_to_int_point(second_point);
	count_delta_and_sign(start, end, &delta, &sign);
	error.x = delta.x - delta.y;
	if ((end.x + fdf->center.x) >= 0 &&
		(end.x + fdf->center.x) < fdf->pic->width)
		draw_pixel(fdf, end);
	while (start.x != end.x || start.y != end.y)
	{
		if ((start.x + fdf->center.x) > 0 &&
			(start.x + fdf->center.x) < fdf->pic->width)
		{
			grad_color(delta, end, &start, first_point->color);
			draw_pixel(fdf, start);
		}
		error.y = error.x * 2;
		update_error_and_start(&start, &error, delta, sign);
	}
	return (1);
}
