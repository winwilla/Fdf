/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 21:00:13 by hdean             #+#    #+#             */
/*   Updated: 2019/04/28 19:52:37 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int j;
	int i;
	int k;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		j = i;
		k = 0;
		while (needle[k] && haystack[j] == needle[k])
		{
			j++;
			k++;
		}
		if (k > 0 && !needle[k])
			return ((char *)(haystack));
		haystack++;
	}
	return (NULL);
}
