/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:26:50 by hdean             #+#    #+#             */
/*   Updated: 2019/12/22 20:51:42 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double			**new_zero_matrix(int row, int col)
{
	double	**new_matrix;
	int		i;

	new_matrix = (double **)malloc(sizeof(double *) * row);
	if (!new_matrix)
	{
		ft_putstr("Error: malloc hasn't work\n");
		return (NULL);
	}
	i = 0;
	while (i < row)
	{
		new_matrix[i] = (double *)ft_memalloc(sizeof(double) * col);
		if (!new_matrix[i])
		{
			ft_putstr("Error: malloc hasn't work\n");
			new_matrix = free_matrix(new_matrix, i);
			return (NULL);
		}
		i++;
	}
	return (new_matrix);
}

static double	**identity_matrix(int size)
{
	double	**matrix;
	int		i;

	i = 0;
	matrix = new_zero_matrix(size, size);
	if (!matrix)
		return (NULL);
	while (i < size)
	{
		matrix[i][i] = 1;
		i++;
	}
	return (matrix);
}

double			**rotation_x(double x_angle)
{
	double **matrix;

	matrix = identity_matrix(3);
	if (!matrix)
		return (NULL);
	x_angle = grad_to_rad(x_angle);
	matrix[1][1] = cos(x_angle);
	matrix[1][2] = -sin(x_angle);
	matrix[2][1] = -matrix[1][2];
	matrix[2][2] = matrix[1][1];
	return (matrix);
}

double			**rotation_y(double y_angle)
{
	double **matrix;

	matrix = identity_matrix(3);
	if (!matrix)
		return (NULL);
	y_angle = grad_to_rad(y_angle);
	matrix[0][0] = cos(y_angle);
	matrix[0][2] = sin(y_angle);
	matrix[2][0] = -matrix[0][2];
	matrix[2][2] = matrix[0][0];
	return (matrix);
}

double			**rotation_z(double z_angle)
{
	double **matrix;

	matrix = identity_matrix(3);
	if (!matrix)
		return (NULL);
	z_angle = grad_to_rad(z_angle);
	matrix[0][0] = cos(z_angle);
	matrix[1][0] = sin(z_angle);
	matrix[0][1] = -matrix[1][0];
	matrix[1][1] = matrix[0][0];
	return (matrix);
}
