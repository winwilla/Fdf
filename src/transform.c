/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:36:29 by hdean             #+#    #+#             */
/*   Updated: 2019/12/22 19:38:04 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		transform_coord(t_mlx *fdf)
{
	double			**rotation_matrix;

	rotation_matrix = count_rotation_matrix(fdf->angle);
	coordinate_rotation(&(fdf->dots), rotation_matrix);
	scale_image_to_current_screen(fdf);
	back_to_local_coord(fdf);
	free_matrix(rotation_matrix, 3);
}

void		scale_coord(t_dbl_point **dots, double scale)
{
	t_dbl_point *tmp;

	tmp = *dots;
	while (tmp)
	{
		tmp->x *= scale;
		tmp->y *= scale;
		tmp->z *= scale;
		tmp = tmp->next;
	}
}

void		coordinate_rotation(t_dbl_point **dots, double **rotation_matrix)
{
	t_dbl_point		*new;
	t_dbl_param		old;

	new = *dots;
	while (new)
	{
		old.x = new->x;
		old.y = new->y;
		old.z = new->z;
		new->x = rotation_matrix[0][0] * old.x +
					rotation_matrix[0][1] * old.y +
						rotation_matrix[0][2] * old.z;
		new->y = rotation_matrix[1][0] * old.x +
					rotation_matrix[1][1] * old.y +
						rotation_matrix[1][2] * old.z;
		new->z = rotation_matrix[2][0] * old.x +
					rotation_matrix[2][1] * old.y +
						rotation_matrix[2][2] * old.z;
		new = new->next;
	}
}

void		scale_image_to_current_screen(t_mlx *fdf)
{
	t_dbl_param		overall;

	overall = count_overall_sizes(fdf->dots);
	if (fdf->pic->width / overall.x > fdf->pic->height / overall.y)
		fdf->scale = (double)(fdf->pic->height - 10) / overall.y;
	else
		fdf->scale = (double)(fdf->pic->width - 10) / overall.x;
	scale_coord(&(fdf->dots), fdf->scale);
}

void		back_to_local_coord(t_mlx *fdf)
{
	t_dbl_point *dots;
	t_dbl_param max;
	t_dbl_param min;
	t_dbl_param r_point;

	max = max_dbl_dot(fdf->dots);
	min = min_dbl_dot(fdf->dots);
	r_point.x = (max.x + min.x) / 2;
	r_point.y = (max.y + min.y) / 2;
	r_point.z = (max.z + min.z) / 2;
	dots = fdf->dots;
	while (dots)
	{
		dots->x -= r_point.x;
		dots->y -= r_point.y;
		dots->z -= r_point.z;
		dots = dots->next;
	}
}
