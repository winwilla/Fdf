/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_color_scheme.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 17:09:13 by hdean             #+#    #+#             */
/*   Updated: 2019/12/22 20:37:25 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_terra_color(t_dbl_param delta, double z)
{
	int	color;

	if (z <= 0)
		count_new_color(&color, delta.x, get_rgb_color(DSEA),
														get_rgb_color(DBLUE));
	else if (fabs(z / delta.y) < 0.3)
		count_new_color(&color, delta.x, get_rgb_color(DGREEN),
														get_rgb_color(TYELLOW));
	else if (fabs(z / delta.y) < 0.8)
		count_new_color(&color, delta.x, get_rgb_color(DYELLOW),
														get_rgb_color(DBROWN));
	else
		count_new_color(&color, delta.x, get_rgb_color(DBROWN),
														get_rgb_color(AWHITE));
	return (color);
}

void		terra_color_scheme(t_mlx *fdf)
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
	delta.y = (min.z < 0) ? max.z : delta.z;
	while (dots)
	{
		if (delta.z == 0)
			dots->color = DGREEN;
		else
		{
			delta.x = 1 - fabs(max.z - copy_dots->z) / delta.z;
			dots->color = count_terra_color(delta, copy_dots->z);
		}
		dots = dots->next;
		copy_dots = copy_dots->next;
	}
}

t_color		get_rgb_color(int color)
{
	t_color rgb;

	rgb.b = color & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.r = (color >> 16) & 0xFF;
	return (rgb);
}
