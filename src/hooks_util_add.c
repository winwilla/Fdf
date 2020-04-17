/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_util_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:16:09 by hdean             #+#    #+#             */
/*   Updated: 2019/12/20 23:43:07 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				value_to_window(t_mlx *fdf)
{
	if (fdf->values_to_win)
		fdf->values_to_win = 0;
	else
		fdf->values_to_win = 1;
	redraw_vectors(fdf);
	return (0);
}

int				close_hook(void *param)
{
	t_mlx *fdf;

	fdf = (t_mlx *)param;
	delete_fdf(&fdf);
	exit(0);
}

void			restart(t_mlx *fdf)
{
	t_dbl_point *dot;
	t_dbl_point *copy_dot;

	free_dots(&fdf->copy_dots);
	fdf->copy_dots = convert_point_values(fdf->pic->points);
	dot = fdf->dots;
	copy_dot = fdf->copy_dots;
	while (dot)
	{
		dot->x = copy_dot->x;
		dot->y = copy_dot->y;
		dot->z = copy_dot->z;
		dot->color = copy_dot->color;
		dot = dot->next;
		copy_dot = copy_dot->next;
	}
	set_setups_for_transform_params(fdf);
	transform_coord(fdf);
	redraw_vectors(fdf);
}

static void		copy_dots_to_dots(t_mlx *fdf)
{
	t_dbl_point *dot;
	t_dbl_point *copy_dot;

	dot = fdf->dots;
	copy_dot = fdf->copy_dots;
	while (dot)
	{
		dot->x = copy_dot->x;
		dot->y = copy_dot->y;
		dot->z = copy_dot->z;
		dot = dot->next;
		copy_dot = copy_dot->next;
	}
}

void			projections(t_mlx *fdf, int key)
{
	if (key == ISO)
	{
		fdf->angle.x = 30;
		fdf->angle.y = 0;
		fdf->angle.z = -45;
	}
	else
	{
		fdf->angle.x = 0;
		fdf->angle.y = 0;
		fdf->angle.z = 0;
	}
	if (key == ZOX)
		fdf->angle.x = 90;
	else if (key == ZOY)
		fdf->angle.y = 90;
	copy_dots_to_dots(fdf);
	transform_coord(fdf);
	fdf->center.x = fdf->pic->width / 2;
	fdf->center.y = fdf->pic->height / 2;
	redraw_vectors(fdf);
}
