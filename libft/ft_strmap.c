/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:31:30 by hdean             #+#    #+#             */
/*   Updated: 2019/08/16 18:50:40 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *ptr;
	char *start;

	start = NULL;
	if (!s || !f || !(ptr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	start = ptr;
	while (*s)
	{
		*ptr = f(*s);
		ptr++;
		s++;
	}
	*ptr = '\0';
	return (start);
}
