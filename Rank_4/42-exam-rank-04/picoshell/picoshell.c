
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
	int fd[2],i = 0, last_fd = -1;
	pid_t pid;
	
	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(fd) == -1)
			return 1;
		pid = fork();
		if (pid == -1)
		{
			if (cmds[i + 1])
			{
				close(fd[0]);
				close(fd[1]);
			}
			return 1;
		}
		if (pid == 0)
		{
			if (last_fd != -1)
			{
				if (dup2(last_fd, 0) == -1)
					exit(1);
				close(last_fd);
			}
			if (cmds{i + 1})
			{
				close(fd[0]);
				if (dup(fd[1], 1) == -1)
					exit(1);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		else
		{
			if (last_fd != -1)
				close(last_fd);
			if (cmds[i + 1])
			{
				close(fd[1]);
				last_fd = fd[0];
			}
		}
		i++;
	}

	while (wait(NULL) > 0)
		;
	return 0;
}

int main(void)
{
	char *cmd1[] = {"echo", "squalala!", NULL};
	char *cmd2[] = {"cat", NULL};
	char *cmd3[] = {"sed", "s|a|b|g", NULL};

	char **pipeline[] = {cmd1, cmd2, cmd3, NULL};

	return picoshell(pipeline);
}