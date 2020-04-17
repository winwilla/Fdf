/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:36:48 by hdean             #+#    #+#             */
/*   Updated: 2019/08/16 18:48:22 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstsize(t_list *begin_list)
{
	size_t	count;
	t_list	*tmp;

	count = 0;
	tmp = begin_list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
