/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:22:16 by fernando          #+#    #+#             */
/*   Updated: 2025/02/19 17:37:19 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	execute_commands(const char *in, const char *argv[],
			const char *out, const char *envp[]);
void	execute_first_child(int pipefd[2], int fd_in,
			const char *cmd, const char *envp[]);
void	execute_second_child(int pipefd[2], int fd_out,
			const char *cmd, const char *envp[]);
void	close_fds_and_wait(int fd_in, int fd_out,
			int pipefd[2], pid_t last_pid);

int	main(int argc, char const *argv[], char const *envp[])
{
	if (argc != 5)
		ft_error_exit("Usage: ./pipex infile cmd1 cmd2 outfile\n", 0);
	execute_commands(argv[1], argv + 1, argv[argc - 1], envp);
	return (0);
}

void	execute_commands(const char *in, const char *argv[],
			const char *out, const char *envp[])
{
	int		pipefd[2];
	int		fd_in;
	int		fd_out;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		ft_error_exit("pipe", 1);
	fd_in = open(in, O_RDONLY);
	if (fd_in == -1)
		perror("open infile failed");
	fd_out = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		perror("open outfile failed");
	pid1 = fork();
	if (pid1 == 0)
		execute_first_child(pipefd, fd_in, (char *)argv[1], envp);
	pid2 = fork();
	if (pid2 == 0)
		execute_second_child(pipefd, fd_out, (char *)argv[2], envp);
	close_fds_and_wait(fd_in, fd_out, pipefd, pid2);
}

void	execute_first_child(int pipefd[2], int fd_in,
			const char *cmd, const char *envp[])
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
		ft_error_exit("dup2 infile failed", 1);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_error_exit("dup2 pipe write failed", 1);
	close(pipefd[0]);
	close(fd_in);
	close(pipefd[1]);
	execute_child(cmd, envp);
}

void	execute_second_child(int pipefd[2], int fd_out,
			const char *cmd, const char *envp[])
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		ft_error_exit("dup2 read failed", 1);
	if (fd_out == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
		ft_error_exit("dup2 outfile failed", 1);
	close(pipefd[1]);
	if (fd_out != -1)
		close(fd_out);
	close(pipefd[0]);
	execute_child(cmd, envp);
}

void	close_fds_and_wait(int fd_in, int fd_out, int pipefd[2], pid_t last_pid)
{
	int		status;
	int		exit_code;
	pid_t	pid;

	exit_code = 0;
	close(fd_in);
	close(fd_out);
	close(pipefd[0]);
	close(pipefd[1]);
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid && WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		pid = wait(&status);
	}
	exit(exit_code);
}
