/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:27:18 by hdean             #+#    #+#             */
/*   Updated: 2019/12/20 23:52:39 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_file		*search_in_list(t_file **files, const int fd)
{
	t_file *list;

	list = *files;
	if (!files)
		return (NULL);
	while (list)
	{
		if (list->fd == fd)
			return (list);
		list = list->next;
	}
	return (NULL);
}

static int			search_in_buf(char **buf, char **line)
{
	char	*str;
	char	*for_free;
	char	*n_symbol;

	if (ft_strlen(*buf) == 0)
		return (0);
	if ((n_symbol = ft_strchr(*buf, '\n')))
	{
		str = ft_strsub(*buf, 0, n_symbol - *buf);
		for_free = *line;
		*line = ft_strjoin(*line, str);
		free(for_free);
		free(str);
		str = ft_strdup(n_symbol + 1);
		ft_strclr(*buf);
		ft_strcpy(*buf, str);
		free(str);
		return (1);
	}
	for_free = *line;
	*line = ft_strjoin(*line, *buf);
	free(for_free);
	ft_strclr(*buf);
	return (0);
}

static void			delete_element(const int fd, t_file **list)
{
	t_file *next;
	t_file *previous;
	t_file *file;

	if ((file = search_in_list(list, fd)))
	{
		next = file->next;
		previous = file->previous;
		if (previous)
			previous->next = next;
		if (next)
			next->previous = previous;
		free(file->buf);
		file->buf = NULL;
		if (file == *list)
			*list = (*list)->next;
		free(file);
		file = NULL;
	}
}

static void			add_in_list(t_file **list, const int fd, char *buf)
{
	t_file	*new;
	t_file	*find;

	if ((find = search_in_list(list, fd)))
	{
		free(find->buf);
		find->buf = ft_strdup(buf);
	}
	else if ((new = (t_file *)malloc(sizeof(t_file)))
				&& (new->buf = ft_strdup(buf)))
	{
		new->fd = fd;
		new->next = NULL;
		new->previous = NULL;
		if (!*list)
			*list = new;
		else
		{
			new->next = *list;
			(*list)->previous = new;
			*list = new;
		}
	}
}

int					get_next_line(const int fd, char **line)
{
	char				*buf;
	static	t_file		*files;
	t_file				*find;

	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, NULL, 0) == -1)
		return (-1);
	*line = NULL;
	find = search_in_list(&files, fd);
	if (files && find && search_in_buf(&(find->buf), line))
		return (1);
	buf = ft_strnew(BUFF_SIZE);
	while ((read(fd, buf, BUFF_SIZE)))
		if ((search_in_buf(&buf, line)))
		{
			add_in_list(&files, fd, buf);
			free(buf);
			return (1);
		}
	free(buf);
	delete_element(fd, &files);
	if (*line)
		return (1);
	return (0);
}
