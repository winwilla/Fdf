/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 23:26:02 by hdean             #+#    #+#             */
/*   Updated: 2019/12/22 20:32:52 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				hex_symb(int c)
{
	return (ft_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

double			grad_to_rad(double angle)
{
	double rad;

	rad = angle * 3.14 / 180;
	return (rad);
}

char			*ft_itoa_double(double old_n)
{
	char			*str;
	char			*ost;
	char			*tmp_str;
	int				n;

	n = round(old_n * 10);
	ost = ft_itoa(n / 10);
	str = ft_strjoin(ost, ".");
	free(ost);
	ost = ft_itoa(abs(n) % 10);
	tmp_str = str;
	str = ft_strjoin(str, ost);
	free(tmp_str);
	free(ost);
	return (str);
}

t_dbl_param		max_dbl_dot(t_dbl_point *dots)
{
	t_dbl_param max;

	max.x = dots->x;
	max.y = dots->y;
	max.z = dots->z;
	while (dots)
	{
		if (dots->x > max.x)
			max.x = dots->x;
		if (dots->y > max.y)
			max.y = dots->y;
		if (dots->z > max.z)
			max.z = dots->z;
		dots = dots->next;
	}
	return (max);
}

t_dbl_param		min_dbl_dot(t_dbl_point *dots)
{
	t_dbl_param min;

	min.x = dots->x;
	min.y = dots->y;
	min.z = dots->z;
	while (dots)
	{
		if (dots->x < min.x)
			min.x = dots->x;
		if (dots->y < min.y)
			min.y = dots->y;
		if (dots->z < min.z)
			min.z = dots->z;
		dots = dots->next;
	}
	return (min);
}
