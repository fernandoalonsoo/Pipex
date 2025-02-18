#include "../pipex.h"

int		execute_commands(char *infile, char const *argv[], char *outfile, int cmds);
void	manage_pipes(int last_pipe, int cmds, int count, int *pipefd);
void	manage_redirection(int count, char *infile, char *outfile);

int	main(int argc, char const *argv[])
{
	char *infile;
	char *outfile;

	infile = (char *) argv[1];
	outfile = (char *) argv[argc - 1];
	if ((argc < 5))
	{
		perror("Invalid argument number. Usage: ./pipex infile command1 command2 outfile\n");
		exit(1);
	}
	execute_commands(infile, argv + 1 ,outfile, argc - 3);
	return 0;
}

int execute_commands(char *infile, char const *argv[], char *outfile, int cmds)
{
	int count;
	int pid;
	int *pipefd;
	int last_pipe;

	count = 1;
	pipefd = malloc(2 * sizeof(int *));
	last_pipe = -1;
	while (count <= cmds)
	{
		if (count != cmds)
		{
			if (pipe(pipefd) == -1) 
				exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == 0)
		{
			manage_pipes(last_pipe, cmds, count, pipefd);
			manage_redirection(count, infile, outfile);
			execute_child((char *)argv[count]);
		}
		else
		{
			if (last_pipe != -1)
				close(last_pipe); 
			last_pipe = pipefd[0];
			close(pipefd[1]); 
		}
		count++;
	}

	while (wait(NULL) > 0);
	free(pipefd);
	return 0;
}

void manage_pipes(int last_pipe, int cmds, int count, int *pipefd)
{
	if (last_pipe != -1)
	{
		if (dup2(last_pipe, STDIN_FILENO) == -1)
		{
			perror("dup2 pipe STDIN");
			exit(EXIT_FAILURE);
		}
		close(last_pipe);
	}

	if (count != cmds)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe STDOUT");
			exit(EXIT_FAILURE);
		}
		close(pipefd[1]);
	}
}

void	manage_redirection(int count, char *infile, char *outfile)
{
	int fd; 

	if (count == 1)
	{
		int fd = open(infile, O_RDONLY);
		if (fd == -1)
		{
			perror("open infile failed");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 infile failed");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}
	else 
	{
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}