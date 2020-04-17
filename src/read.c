/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:45:56 by hdean             #+#    #+#             */
/*   Updated: 2019/12/20 21:59:59 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_line(char *buf)
{
	while (*buf != '\0')
	{
		if (!(*buf == ',' || *buf == 'x' || *buf == '-' ||
				ft_isspace(*buf) || hex_symb(*buf)))
		{
			ft_putstr("Error: forbidden symbol ");
			write(1, buf, 1);
			ft_putstr("\n");
			return (0);
		}
		if (*buf == ',' && !(!ft_strncmp(",0x", buf, 3) &&
			*(buf - 1) && ft_isdigit(*(buf - 1))))
		{
			ft_putstr("Error: wrong color\n");
			return (0);
		}
		if (*buf == 'x' && !(*(buf + 1) && hex_symb(*(buf + 1))))
		{
			ft_putstr("Error: wrong color\n");
			return (0);
		}
		buf++;
	}
	return (1);
}

static int	parse_from_line(char *buf, t_image *pic, t_point *line)
{
	line->color = AWHITE;
	if (!(check_line(buf) && parse_point(&(pic->points), buf, *line)))
	{
		ft_putstr("Error: invalid points\n");
		return (0);
	}
	line->y++;
	if (line->y == 1)
		line->x = pic->points->x;
	if (pic->points->x != line->x)
	{
		ft_putstr("Error: line length error\n");
		return (0);
	}
	return (1);
}

static int	check_error(t_point *points)
{
	if (!points)
	{
		ft_putstr("Error: no points in the file\n");
		return (1);
	}
	if (points->x == 0 && points->y == 0)
	{
		ft_putstr("Error: only one point in the file\n");
		return (1);
	}
	return (0);
}

static int	check_fd(int fd, char *filename)
{
	if (fd < 0)
	{
		ft_putstr("Error: file ");
		write(1, filename, ft_strlen(filename));
		ft_putstr(" doesn't exist\n");
		return (0);
	}
	if (fd == 0 || read(fd, NULL, 0) == -1)
	{
		ft_putstr("Error: can't read the file\n");
		return (0);
	}
	return (1);
}

int			read_and_valid(t_image *pic)
{
	int			fd;
	char		*buf;
	t_point		line;

	fd = open(pic->name, O_RDONLY);
	if (!(check_fd(fd, pic->name)))
		return (0);
	buf = NULL;
	line.y = 0;
	line.x = 0;
	while (get_next_line(fd, &buf))
	{
		if (!parse_from_line(buf, pic, &line))
		{
			free(buf);
			close(fd);
			return (0);
		}
		free(buf);
	}
	close(fd);
	if (check_error(pic->points))
		return (0);
	return (1);
}
