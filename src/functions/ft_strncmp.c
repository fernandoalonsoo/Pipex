/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fealonso <fealonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:36:37 by fealonso          #+#    #+#             */
/*   Updated: 2024/09/22 21:22:56 by fealonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;
	size_t			i;

	p = (unsigned char *) s1;
	q = (unsigned char *) s2;
	i = 0;
	while (i < n && (p[i] != '\0' || q[i] != '\0'))
	{
		if (p[i] != q[i])
			return (p[i] - q[i]);
		i++;
	}
	return (0);
}
