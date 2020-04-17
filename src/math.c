/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 00:00:11 by hdean             #+#    #+#             */
/*   Updated: 2019/12/22 20:57:56 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	**matrix_multipl(double **first, double **second, int size)
{
	int			i;
	int			j;
	int			k;
	double		**result;

	result = new_zero_matrix(size, size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			k = 0;
			while (k < size)
			{
				result[i][j] += first[i][k] * second[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

t_dbl_param		count_overall_sizes(t_dbl_point *dots)
{
	t_dbl_param max;
	t_dbl_param min;
	t_dbl_param overall;

	max = max_dbl_dot(dots);
	min = min_dbl_dot(dots);
	overall.x = fabs(max.x - min.x);
	overall.y = fabs(max.y - min.y);
	overall.z = fabs(max.z - min.z);
	return (overall);
}

double			**count_rotation_matrix(t_dbl_param angle)
{
	double	**rot_x;
	double	**rot_y;
	double	**rot_z;
	double	**rot_x_y;
	double	**rot_x_y_z;

	rot_x = rotation_x(angle.x);
	rot_y = rotation_y(angle.y);
	rot_z = rotation_z(angle.z);
	rot_x_y = matrix_multipl(rot_x, rot_y, 3);
	rot_x_y_z = matrix_multipl(rot_x_y, rot_z, 3);
	rot_x = free_matrix(rot_x, 3);
	rot_y = free_matrix(rot_y, 3);
	rot_z = free_matrix(rot_z, 3);
	rot_x_y = free_matrix(rot_x_y, 3);
	return (rot_x_y_z);
}
