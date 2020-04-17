/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 19:35:45 by hdean             #+#    #+#             */
/*   Updated: 2019/10/17 21:22:03 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *str;
	char cd;

	str = (char *)s;
	cd = (char)c;
	while (*str != cd && *str)
		str++;
	if (*str == cd)
		return ((char *)str);
	return (NULL);
}
