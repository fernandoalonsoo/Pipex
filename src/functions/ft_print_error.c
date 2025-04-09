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

int	ft_print_string_fd(const char *str, int fd)
{
	int	len;

	len = ft_strlen(str);
	return (write(fd, str, len));
}

void	ft_error_exit(const char *msg, int exit_code)
{
	if (exit_code == 1)
		perror(msg);
	else
		ft_print_string_fd(msg, 2);
	exit(exit_code);
}
