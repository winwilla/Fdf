/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 21:52:03 by hdean             #+#    #+#             */
/*   Updated: 2019/12/20 23:45:26 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_int_coord	count_max_xyz(t_point *points)
{
	t_int_coord	max;

	max.x = points->x;
	max.y = points->y;
	max.z = points->z;
	while (points)
	{
		if (points->x > max.x)
			max.x = points->x;
		if (points->y > max.y)
			max.y = points->y;
		if (points->z > max.z)
			max.z = points->z;
		points = points->next;
	}
	return (max);
}

static void			local_shift_pic_coord(t_image *pic)
{
	t_point *dots;
	int		dx;
	int		dy;

	dx = pic->max_xyz.x / 2 - 1;
	dy = pic->max_xyz.y / 2 - 1;
	dots = pic->points;
	while (dots)
	{
		dots->x -= dx;
		dots->y -= dy;
		dots = dots->next;
	}
}

static void			check_params(int ac, char **av, t_image *pic)
{
	if (ac == 2)
	{
		pic->height = HEIGHT;
		pic->width = WIDTH;
	}
	else
	{
		pic->height = ft_atoi(av[2]);
		pic->width = ft_atoi(av[3]);
		if (pic->width < 100 || pic->height < 100)
		{
			pic->height = HEIGHT;
			pic->width = WIDTH;
			ft_putstr("Warning: ");
			ft_putstr("height and width of the window set by default\n");
		}
	}
	pic->name = av[1];
	pic->points = NULL;
}

int					main(int ac, char **av)
{
	t_image pic;

	if (ac != 2 && ac != 4)
	{
		ft_putstr("usage: ./fdf map_file [map_height map_width]\n");
		return (1);
	}
	check_params(ac, av, &pic);
	if (read_and_valid(&pic))
	{
		pic.max_xyz = count_max_xyz(pic.points);
		if (pic.height / (pic.max_xyz.y + 1) < pic.width / (pic.max_xyz.x + 1))
			pic.max_scale = 20 * pic.width / (pic.max_xyz.x + 1);
		else
			pic.max_scale = 20 * pic.height / (pic.max_xyz.y + 1);
		local_shift_pic_coord(&pic);
		draw_fdf(&pic);
	}
	delete_image_pic(&pic);
	return (0);
}
