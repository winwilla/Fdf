/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 00:13:34 by hdean             #+#    #+#             */
/*   Updated: 2019/04/30 20:23:25 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_arr(char **arr, size_t n, int in)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (arr)
	{
		while (i < n)
		{
			j = 0;
			while (arr[i][j])
			{
				write(in, &arr[i][j], 1);
				j++;
			}
			write(in, "\n", 1);
			i++;
		}
	}
}
