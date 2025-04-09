/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fealonso <fealonso@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 10:58:29 by fealonso          #+#    #+#             */
/*   Updated: 2024/12/29 11:10:56 by fealonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

int	ft_print_char(char c);

int	ft_print_string(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_print_string("(null)"));
	while (str[i] != '\0')
		ft_print_char(str[i++]);
	return (i);
}

int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}
