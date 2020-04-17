/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 22:52:24 by hdean             #+#    #+#             */
/*   Updated: 2019/12/08 19:56:57 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		add_new_dbl_point(t_dbl_point **list, t_dbl_point dot)
{
	t_dbl_point *new;

	if (!(new = (t_dbl_point *)malloc(sizeof(t_dbl_point))))
	{
		ft_putstr("Error: malloc hasn't work\n");
		return (0);
	}
	new->x = dot.x;
	new->y = dot.y;
	new->z = dot.z;
	new->color = dot.color;
	if (!*list)
	{
		*list = new;
		(*list)->next = NULL;
	}
	else
	{
		new->next = *list;
		*list = new;
	}
	return (1);
}

t_dbl_point		*convert_point_values(t_point *points)
{
	t_dbl_point *new;
	t_dbl_point *tmp;
	t_dbl_point dot;

	new = NULL;
	while (points)
	{
		dot.x = points->x;
		dot.y = points->y;
		dot.z = points->z;
		dot.color = points->color;
		if (!add_new_dbl_point(&new, dot))
		{
			while (new)
			{
				tmp = new->next;
				free(new);
				new = tmp;
			}
			return (NULL);
		}
		points = points->next;
	}
	return (new);
}

static int		read_color(char *buf, int *color)
{
	int i;
	int b;

	buf += 2;
	i = 0;
	b = 4;
	*color = 0;
	while (*buf && !ft_isspace(*buf))
	{
		if (*buf && ft_isdigit(*buf))
			*color = (*color << b) + *buf - '0';
		else if (*buf >= 'A' && *buf <= 'F')
			*color = (*color << b) + *buf - 'A' + 10;
		else if (*buf >= 'a' && *buf <= 'f')
			*color = (*color << b) + *buf - 'a' + 10;
		buf++;
		if (++i > 6)
		{
			ft_putstr("Error: wrong color\n");
			return (0);
		}
	}
	return (1);
}

static int		add_new_int_point(t_point **list, t_point dot)
{
	t_point *new;

	if (!(new = (t_point *)malloc(sizeof(t_point))))
	{
		ft_putstr("Error: malloc hasn't work\n");
		return (0);
	}
	new->x = dot.x;
	new->y = dot.y;
	new->z = dot.z;
	new->color = dot.color;
	if (!*list)
	{
		*list = new;
		(*list)->next = NULL;
	}
	else
	{
		new->next = *list;
		*list = new;
	}
	return (1);
}

int				parse_point(t_point **list, char *buf, t_point dot)
{
	dot.x = 0;
	dot.z = 0;
	while (*buf != '\0')
	{
		while (*buf && ft_isspace(*buf))
			buf++;
		if (*buf && (ft_isdigit(*buf) ||
						(*buf == '-' && *(buf + 1) && ft_isdigit(*(buf + 1)))))
		{
			dot.z = ft_atoi(buf);
			while (*buf && ft_isdigit(*buf))
				buf++;
			if ((*buf && *buf == ',' && !read_color(++buf, &dot.color)) ||
							!add_new_int_point(list, dot))
				return (0);
			while (*buf && !ft_isspace(*buf))
				buf++;
			dot.x++;
		}
		else if (*buf)
			return (0);
	}
	if (dot.x == 0 && dot.y == 0)
		return (0);
	return (1);
}
