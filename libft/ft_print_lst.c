/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:43:08 by hdean             #+#    #+#             */
/*   Updated: 2019/04/30 17:50:24 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_putstr_inp(char const *s, int i)
{
	while (*s)
		write(i, s++, 1);
}

void			ft_print_lst(t_list *start, int i)
{
	t_list *ptr;

	if (start)
	{
		ptr = start;
		while (ptr != NULL)
		{
			ft_putstr_inp(ptr->content, i);
			write(i, "\n", 1);
			ptr = ptr->next;
		}
	}
}
