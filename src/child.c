
#include "../pipex.h"

static char *find_command_path(char *cmd);

void	execute_child(char *cmd)
{
	char **argv;

	argv = ft_split(cmd, ' ');
	char *cmd_path = find_command_path(argv[0]);
	if (!cmd_path)
	{
		perror("Command not found");
		exit(1);
	}
	execve(cmd_path, argv, NULL);

	perror("execve failed");
	exit(1);
}

static char *find_command_path(char *cmd)
{
	char 	*path;
	char 	**paths;
	char	*cmd_path;

	path = getenv("PATH");
	paths = ft_split(path, ':');

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		paths++;
	}
	return (NULL);
}
