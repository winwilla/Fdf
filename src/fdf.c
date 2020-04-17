/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 00:47:09 by hdean             #+#    #+#             */
/*   Updated: 2019/12/22 18:14:50 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			set_setups_for_transform_params(t_mlx *fdf)
{
	fdf->bits_per_pixel = 32;
	fdf->endian = 0;
	fdf->angle.x = 30;
	fdf->angle.y = 0;
	fdf->angle.z = -45;
	fdf->scale = 1;
	fdf->center.x = fdf->pic->width / 2;
	fdf->center.y = fdf->pic->height / 2;
	fdf->center.z = 0;
	fdf->mouse.press = 0;
	fdf->mouse.old_x = WIDTH / 2;
	fdf->mouse.old_y = HEIGHT / 2;
	fdf->color_scheme = 0;
	fdf->values_to_win = 1;
}

static t_mlx	*setups_for_fdf(t_image *pic)
{
	t_mlx *fdf;

	if (!(fdf = (t_mlx *)malloc(sizeof(t_mlx))))
	{
		ft_putstr("Error: malloc hasn't worked.\n");
		return (NULL);
	}
	fdf->pic = pic;
	fdf->line_size = pic->width;
	if (!(fdf->dots = convert_point_values(pic->points)) ||
		!(fdf->copy_dots = convert_point_values(pic->points)) ||
		!(fdf->z_buffer = new_zero_matrix(fdf->pic->height, fdf->pic->width)))
	{
		delete_fdf(&fdf);
		return (NULL);
	}
	set_setups_for_transform_params(fdf);
	transform_coord(fdf);
	return (fdf);
}

static int		hooks(t_mlx *fdf)
{
	mlx_hook(fdf->win_ptr, 2, (1L << 2), key_press, fdf);
	mlx_hook(fdf->win_ptr, 17, (1L << 17), close_hook, fdf);
	mlx_hook(fdf->win_ptr, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->win_ptr, 5, 0, mouse_release, fdf);
	mlx_hook(fdf->win_ptr, 6, 0, mouse_move, fdf);
	return (1);
}

void			draw_fdf(t_image *pic)
{
	t_mlx	*fdf;
	int		menu;

	if (!(fdf = setups_for_fdf(pic)))
		return ;
	menu = (pic->height >= HEIGHT) ? 250 : 0;
	if (!(fdf->mlx_ptr = mlx_init()) ||
		!(fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, pic->width + menu + 10,
		pic->height + 10, pic->name)) ||
		!(fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, pic->width,
		pic->height)) || !(fdf->data = mlx_get_data_addr(fdf->img_ptr,
		&fdf->bits_per_pixel, &fdf->line_size, &fdf->endian)))
	{
		ft_putstr("Error: mlx library doesn't work\n");
		delete_fdf(&fdf);
		return ;
	}
	if (menu)
		put_menu(fdf);
	draw_vectors(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 5, 5);
	put_params_menu_to_window(fdf);
	hooks(fdf);
	mlx_loop(fdf->mlx_ptr);
	delete_fdf(&fdf);
}
