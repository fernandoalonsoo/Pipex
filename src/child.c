/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:41:53 by fernando          #+#    #+#             */
/*   Updated: 2025/02/19 17:42:01 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*find_command_path(char *cmd, char *const envp[]);
static char	*get_path_from_env(char *const envp[]);
static void	free_split(char **split);

void	execute_child(const char *cmd, const char *envp[])
{
	char	**argv;
	char	*cmd_path;

	argv = ft_split(cmd, ' ');
	if (!argv || !argv[0])
	{
		free_split(argv);
		ft_error_exit("Invalid command", 1);
	}
	cmd_path = find_command_path(argv[0], (char *const *)envp);
	if (!cmd_path)
	{
		free_split(argv);
		ft_error_exit("Command not found\n", 127);
	}
	execve(cmd_path, argv, (char *const *)envp);
	perror("execve failed");
	free(cmd_path);
	free_split(argv);
	exit(1);
}

static char	*find_command_path(char *cmd, char *const envp[])
{
	char	**paths;
	char	*cmd_path;
	char	*temp;
	char	*path;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	path = get_path_from_env(envp);
	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free_split(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_split(paths);
	return (NULL);
}

static char	*get_path_from_env(char *const envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}
