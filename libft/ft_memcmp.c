/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 20:40:51 by hdean             #+#    #+#             */
/*   Updated: 2019/08/16 18:48:40 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				d;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n-- != 0)
	{
		d = *str1++ - *str2++;
		if (d != 0)
			return (d);
	}
	return (0);
}
