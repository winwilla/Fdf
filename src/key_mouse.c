/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 23:42:08 by hdean             #+#    #+#             */
/*   Updated: 2019/12/22 18:18:08 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			key_press(int key, void *param)
{
	t_mlx	*fdf;

	fdf = (t_mlx *)param;
	if (key == ESC)
		close_hook(param);
	if (key == PLUS_N || key == PLUS || key == MINUS_N || key == MINUS)
		scale(fdf, key);
	else if (key == LEFT || key == RIGHT || key == UP || key == DOWN)
		move(fdf, key);
	else if (key == CENTER || key == FIT)
		center(fdf, key);
	else if (key == R_X_NN || key == R_X_PN || key == R_Y_NN || key == R_Y_PN ||
			key == R_Z_PN || key == R_Z_NN)
		rotate(fdf, key);
	else if (key == PARALLEL || key == ISO || key == ZOX || key == ZOY)
		projections(fdf, key);
	else if (key == SPACE)
		restart(fdf);
	else if (key == COLOR_A || key == COLOR_B || key == RESET_COLOR)
		color_scheme(fdf, key);
	else if (key == VALUE)
		value_to_window(fdf);
	return (0);
}

int			mouse_press(int button, int x, int y, void *param)
{
	t_mlx	*fdf;

	(void)x;
	(void)y;
	fdf = (t_mlx *)param;
	if (button == MOUSE_UP || button == MOUSE_DOWN)
		scale(fdf, button);
	else if (button == MOUSE_LEFT)
	{
		fdf->mouse.press = 1;
		fdf->mouse.old_x = x;
		fdf->mouse.old_y = y;
	}
	return (0);
}

int			mouse_release(int button, int x, int y, void *param)
{
	t_mlx	*fdf;

	(void)x;
	(void)y;
	(void)button;
	fdf = (t_mlx *)param;
	fdf->mouse.press = 0;
	return (0);
}

static void	check_angles(t_dbl_param *angle)
{
	if (angle->x >= 360)
		angle->x -= 360;
	else if (angle->x <= -360)
		angle->x += 360;
	else if (angle->y >= 360)
		angle->y -= 360;
	else if (angle->y <= -360)
		angle->y += 360;
}

int			mouse_move(int x, int y, void *param)
{
	t_mlx			*fdf;
	double			**rotation_matrix;
	t_dbl_param		angle;

	fdf = (t_mlx *)param;
	if (fdf->mouse.press)
	{
		angle.x = (-y + fdf->mouse.old_y) / 2;
		angle.y = (x - fdf->mouse.old_x) / 2;
		angle.z = 0;
		fdf->angle.x += angle.x;
		fdf->angle.y += angle.y;
		check_angles(&fdf->angle);
		rotation_matrix = count_rotation_matrix(angle);
		coordinate_rotation(&(fdf->dots), rotation_matrix);
		free_matrix(rotation_matrix, 3);
		fdf->mouse.old_x = x;
		fdf->mouse.old_y = y;
		redraw_vectors(fdf);
	}
	return (0);
}
