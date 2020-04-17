/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 23:12:46 by hdean             #+#    #+#             */
/*   Updated: 2019/12/20 23:42:19 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		count_delta_angel(t_dbl_param *angle, int key)
{
	angle->x = 0;
	angle->y = 0;
	angle->z = 0;
	if (key == R_X_PN)
		angle->x = 10;
	else if (key == R_X_NN)
		angle->x = -10;
	else if (key == R_Y_PN)
		angle->y = 10;
	else if (key == R_Y_NN)
		angle->y = -10;
	else if (key == R_Z_PN)
		angle->z = 10;
	else if (key == R_Z_NN)
		angle->z = -10;
}

void			rotate(t_mlx *fdf, int key)
{
	double		**xyz;
	t_dbl_param	angle;

	count_delta_angel(&angle, key);
	if (angle.x && (fdf->angle.x += angle.x) >= 360)
		fdf->angle.x -= 360;
	else if (angle.x && (fdf->angle.x += angle.x) <= -360)
		fdf->angle.x += 360;
	else if (angle.y && (fdf->angle.y += angle.y) >= 360)
		fdf->angle.y -= 360;
	else if (angle.y && (fdf->angle.y += angle.y) <= -360)
		fdf->angle.y += 360;
	else if (angle.z && (fdf->angle.z += angle.z) >= 360)
		fdf->angle.z -= 360;
	else if (angle.z && (fdf->angle.z += angle.z) <= -360)
		fdf->angle.z += 360;
	xyz = count_rotation_matrix(angle);
	coordinate_rotation(&fdf->dots, xyz);
	free_matrix(xyz, 3);
	redraw_vectors(fdf);
}

void			center(t_mlx *fdf, int key)
{
	double old_scale;
	double old_z;

	if (key == FIT)
	{
		old_scale = fdf->scale;
		old_z = fdf->dots->z;
		scale_image_to_current_screen(fdf);
		fdf->scale = fdf->dots->z * old_scale / old_z;
		back_to_local_coord(fdf);
	}
	fdf->center.x = fdf->pic->width / 2;
	fdf->center.y = fdf->pic->height / 2;
	redraw_vectors(fdf);
}

void			scale(t_mlx *fdf, int key)
{
	double		scale;

	if (key == PLUS || key == PLUS_N || key == MOUSE_UP)
		scale = 1.1;
	else
		scale = 0.9;
	fdf->scale *= scale;
	if (fdf->scale <= fdf->pic->max_scale && fdf->scale >= 0.01)
		scale_coord(&(fdf->dots), scale);
	else if (fdf->scale < 0.01)
		fdf->scale = 0.01;
	else
		fdf->scale = fdf->pic->max_scale;
	redraw_vectors(fdf);
}

void			move(t_mlx *fdf, int key)
{
	int			dx;
	int			dy;
	t_dbl_point	*dots;

	dx = 0;
	dy = 0;
	dots = fdf->dots;
	if (key == LEFT)
		dx = -10;
	else if (key == RIGHT)
		dx = 10;
	else if (key == UP)
		dy = 10;
	else if (key == DOWN)
		dy = -10;
	fdf->center.x += dx;
	fdf->center.y += dy;
	redraw_vectors(fdf);
}
