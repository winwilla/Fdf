/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:49:41 by hdean             #+#    #+#             */
/*   Updated: 2019/12/22 20:33:16 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		draw_vectors_horizont(t_mlx *fdf)
{
	t_dbl_point *end_point;
	t_dbl_point *start_point;
	int			i;
	int			j;

	i = 0;
	j = 0;
	start_point = fdf->dots;
	while (start_point->next && j++ < fdf->pic->max_xyz.y + 1)
	{
		i = 0;
		while (start_point->next && i++ < fdf->pic->max_xyz.x)
		{
			end_point = start_point->next;
			draw_line(start_point, end_point, fdf);
			if (start_point->next)
				start_point = start_point->next;
		}
		if (start_point->next)
			start_point = start_point->next;
	}
}

static void		draw_vectors_vertical(t_mlx *fdf)
{
	t_dbl_point *end_point;
	t_dbl_point *start_point;
	int			i;
	int			j;

	i = 0;
	j = 0;
	start_point = fdf->dots;
	end_point = start_point;
	while (end_point->next && i++ <= fdf->pic->max_xyz.x)
		end_point = end_point->next;
	while (j++ < fdf->pic->max_xyz.y)
	{
		i = 0;
		while (i++ <= fdf->pic->max_xyz.x)
		{
			draw_line(start_point, end_point, fdf);
			end_point = end_point->next;
			start_point = start_point->next;
		}
	}
}

static void		clean_z_buffer(t_mlx *fdf)
{
	int row;
	int col;

	row = 0;
	col = 0;
	while (row++ < fdf->pic->height - 1)
	{
		col = 0;
		while (col++ < fdf->pic->width - 1)
			fdf->z_buffer[row][col] = 0;
	}
}

int				draw_vectors(t_mlx *fdf)
{
	draw_vectors_vertical(fdf);
	draw_vectors_horizont(fdf);
	clean_z_buffer(fdf);
	return (1);
}

int				redraw_vectors(t_mlx *fdf)
{
	clear_image(fdf);
	draw_vectors(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 5, 5);
	if (fdf->values_to_win)
		put_params_menu_to_window(fdf);
	return (1);
}
