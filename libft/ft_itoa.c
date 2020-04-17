/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 19:03:24 by hdean             #+#    #+#             */
/*   Updated: 2019/08/16 18:47:50 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	tmp;

	len = ft_count_digits(n);
	if (!(str = ft_strnew(len)))
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		tmp = -n;
	}
	else
		tmp = n;
	while (tmp > 0)
	{
		str[--len] = tmp % 10 + '0';
		tmp /= 10;
	}
	return (str);
}
