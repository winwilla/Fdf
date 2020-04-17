/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:31:48 by hdean             #+#    #+#             */
/*   Updated: 2019/08/16 18:47:21 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MAX_L 9223372036854775807

int		ft_atoi(const char *str)
{
	unsigned long long int	num;
	int						sign;

	sign = 1;
	num = 0;
	while (ft_isspace(*str))
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (num > MAX_L && sign == 1)
			return (-1);
		else if (num > MAX_L && sign == -1)
			return (0);
		num = num * 10 + *str - '0';
		str++;
	}
	return ((int)(num * sign));
}
