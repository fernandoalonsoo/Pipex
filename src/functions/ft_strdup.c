/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fealonso <fealonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:01:19 by fealonso          #+#    #+#             */
/*   Updated: 2024/09/22 20:34:40 by fealonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

static char	*ft_copy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*p;

	p = malloc(ft_strlen(src) + 1);
	if (p)
		ft_copy(p, src);
	return (p);
}
