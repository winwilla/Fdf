/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 22:30:49 by hdean             #+#    #+#             */
/*   Updated: 2019/08/16 18:49:45 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long int tmp;

	tmp = (long int)n;
	if (tmp < 0)
	{
		ft_putchar('-');
		tmp *= -1;
	}
	if (tmp >= 0 && tmp < 10)
		ft_putchar(tmp + '0');
	else if (tmp >= 10)
	{
		ft_putnbr(tmp / 10);
		ft_putnbr(tmp % 10);
	}
}
