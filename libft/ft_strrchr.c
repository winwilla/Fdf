/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 19:50:14 by hdean             #+#    #+#             */
/*   Updated: 2019/04/21 15:16:13 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*str;
	char	sr;

	sr = (char)c;
	str = (char *)s;
	len = ft_strlen(str);
	if (sr == '\0')
		return (&str[len]);
	if (!str)
		return (str++);
	while (len > 0)
	{
		if (str[len - 1] == sr)
			return (&str[len - 1]);
		len--;
	}
	return (NULL);
}
