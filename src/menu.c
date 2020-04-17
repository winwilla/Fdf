/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 00:15:49 by hdean             #+#    #+#             */
/*   Updated: 2019/12/22 22:35:57 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotation_translation_lines(t_mlx *fdf, int x, int y)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = fdf->mlx_ptr;
	win_ptr = fdf->win_ptr;
	mlx_string_put(mlx_ptr, win_ptr, x, y, BPINK, "Rotation");
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y + 20, AWHITE, "Z:");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 40, AWHITE, "CW:    [num 2]");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 60, AWHITE, "CCW:   [num 1]");
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y + 80, AWHITE, "Y:");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 100, AWHITE, "CW:    [num 5]");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 120, AWHITE, "CCW:   [num 4]");
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y + 140, AWHITE, "X:");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 160, AWHITE, "CW:    [num 8]");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 180, AWHITE, "CCW:   [num 7]");
	mlx_string_put(mlx_ptr, win_ptr, x + 10, y + 200, AWHITE,
														"Left mouse button");
	mlx_string_put(mlx_ptr, win_ptr, x, y + 240, BPINK, "Translation: arrows");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 260, AWHITE, "Left:  [<]");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 280, AWHITE, "Right: [>]");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 300, AWHITE, "Up:    [^]");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 320, AWHITE, "Left:  [v]");
}

static void	scaling_and_color_scheme(t_mlx *fdf, int x, int y)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = fdf->mlx_ptr;
	win_ptr = fdf->win_ptr;
	mlx_string_put(mlx_ptr, win_ptr, x, y, BPINK, "Scaling");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 20, AWHITE, "+:  [num +] [+]");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 40,
												AWHITE, "    [mouse weel ^]");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 60, AWHITE, "-:  [num -] [-]");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 80,
												AWHITE, "    [mouse weel v]");
	mlx_string_put(mlx_ptr, win_ptr, x, y + 120, BPINK, "Color scheme");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 140,
													AWHITE, "change:[Q][W]");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 160, AWHITE, "reset: [E]");
}

static void	projections_and_other_help_commands(t_mlx *fdf, int x, int y)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = fdf->mlx_ptr;
	win_ptr = fdf->win_ptr;
	mlx_string_put(mlx_ptr, win_ptr, x, y, BPINK, "Projections");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 20,
												AWHITE, "ISO:   [I] ZOY:[P]");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 40,
												AWHITE, "XOY:   [O] ZOX:[{]");
	mlx_string_put(mlx_ptr, win_ptr, x, y + 80, BPINK, "View parameters");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 100,
											AWHITE, "Angles and scale: [Z]");
	mlx_string_put(mlx_ptr, win_ptr, x, y + 140, BPINK, "Centered");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 140, AWHITE, "       [C]");
	mlx_string_put(mlx_ptr, win_ptr, x, y + 180, BPINK, "Fit");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 180, AWHITE, "       [V]");
	mlx_string_put(mlx_ptr, win_ptr, x, y + 220, BPINK, "Reset");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 220, AWHITE, "       [SPACE]");
	mlx_string_put(mlx_ptr, win_ptr, x, y + 260, BPINK, "Exit");
	mlx_string_put(mlx_ptr, win_ptr, x + 20, y + 260, AWHITE, "       [ESC]");
}

void		put_menu(t_mlx *fdf)
{
	int		x;
	int		y;
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = fdf->mlx_ptr;
	win_ptr = fdf->win_ptr;
	x = fdf->pic->width + 10;
	y = 50;
	mlx_string_put(mlx_ptr, win_ptr, x, y, CSEA, "CONTROLS");
	rotation_translation_lines(fdf, x, y + 40);
	scaling_and_color_scheme(fdf, x, y + 400);
	projections_and_other_help_commands(fdf, x, y + 600);
}

void		put_params_menu_to_window(t_mlx *fdf)
{
	char *str_z;
	char *str_y;
	char *str_x;
	char *str_scale;

	str_z = ft_itoa_double(fdf->angle.z);
	str_y = ft_itoa_double(fdf->angle.y);
	str_x = ft_itoa_double(fdf->angle.x);
	str_scale = ft_itoa_double(fdf->scale);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 10, CSEA, "Angles:");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 30, CSEA, "Z: ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 30, DYELLOW, str_z);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 50, CSEA, "Y: ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 50, DYELLOW, str_y);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 70, CSEA, "X: ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 70, DYELLOW, str_x);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 90, CSEA, "Scale: ");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 80, 90, DYELLOW, str_scale);
	free(str_z);
	free(str_y);
	free(str_x);
	free(str_scale);
}
