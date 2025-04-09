/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:05:00 by fernando          #+#    #+#             */
/*   Updated: 2025/02/19 18:05:07 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

# include "string.h"

void	execute_child(const char *cmd, const char *envp[]);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *src);
void	ft_error_exit(const char *msg, int use_perror);
int		ft_print_string(const char *str);

#endif
