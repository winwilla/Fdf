/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 22:10:17 by hdean             #+#    #+#             */
/*   Updated: 2019/12/20 23:41:38 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		delete_image_pic(t_image *pic)
{
	t_point		*tmp;

	while (pic->points)
	{
		tmp = pic->points->next;
		free(pic->points);
		pic->points = tmp;
	}
	pic->points = NULL;
}

double		**free_matrix(double **matrix, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
	return (matrix);
}

void		delete_fdf(t_mlx **fdf)
{
	t_mlx		*tmp;
	t_dbl_point	*tmp_point;

	tmp = *fdf;
	while (tmp->dots)
	{
		tmp_point = tmp->dots->next;
		free(tmp->dots);
		tmp->dots = tmp_point;
	}
	while (tmp->copy_dots)
	{
		tmp_point = tmp->copy_dots->next;
		free(tmp->copy_dots);
		tmp->copy_dots = tmp_point;
	}
	if (tmp->pic->points)
		delete_image_pic(tmp->pic);
	free_matrix(tmp->z_buffer, tmp->pic->height);
	if (tmp->img_ptr)
		mlx_destroy_image(tmp->mlx_ptr, tmp->img_ptr);
	if (tmp->win_ptr)
		mlx_destroy_window(tmp->mlx_ptr, tmp->win_ptr);
	free(tmp);
	*fdf = NULL;
}

void		free_dots(t_dbl_point **list)
{
	t_dbl_point *tmp;
	t_dbl_point *dots;

	dots = *list;
	while (dots)
	{
		tmp = dots->next;
		free(dots);
		dots = tmp;
	}
}

void		clear_image(t_mlx *fdf)
{
	ft_bzero(fdf->data, fdf->pic->width * fdf->pic->height *
												(fdf->bits_per_pixel / 8));
}
