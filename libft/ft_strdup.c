/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 20:24:03 by hdean             #+#    #+#             */
/*   Updated: 2019/04/30 17:39:04 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ptr;

	if (!(ptr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	ft_strcpy(ptr, str);
	return (ptr);
}
