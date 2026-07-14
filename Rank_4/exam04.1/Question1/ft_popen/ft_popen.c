# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	int fd[2];
	if (pipe(fd) == -1)
		return (-1);
	pid_t pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit(1);
			close(fd[0]);
			close(fd[1]);
		}
		if (type == 'w')
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				exit(1);
			close(fd[0]);
			close(fd[1]);
		}
		execvp(file, argv);
		exit(1);
	}
	if (type == 'r')
	{
		close(fd[1]);
		return (fd[0]);
	}
	if (type == 'w')
	{
		close(fd[0]);
		return (fd[1]);
	}
	return (-1);
}
