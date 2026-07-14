
/*
Allowed functions:
pipe, fork, dup2, execvp, close, exit, wait

Write the following function:

	int picoshell(char **cmds[])

It has to simulate the pipe. cmds[i] contains the command with its arguments.
Use execvp(cmds[i][0], cmds) to execute a command.
It has to return 1, if a command fail. Do not leak file descriptors.
In the exam, a main file will be given to test your picoshell
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void piping(char ***cmds, int index, int *res, int saved_stdin, int saved_stdout)
{
	int fd[2];

	pipe(fd);
	if (cmds[index + 1])
		dup2(fd[1], STDOUT_FILENO);
	if (fork() == 0)
	{
		close(fd[0]);
		close(fd[1]);
		close(saved_stdin);
		close(saved_stdout);
		execvp(cmds[index][0], cmds[index]);
		exit(1);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (cmds[index + 1] == NULL)
	{
		dup2(saved_stdin, STDIN_FILENO);
		int status;
		while (wait(&status) != -1)
		{
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
                *res = 1;
		}
		return ;
	}
	piping(cmds, index + 1, res, saved_stdin, saved_stdout);
}

int picoshell(char **cmds[])
{
	int saved_stdin = dup2(STDIN_FILENO, 1000);
	int saved_stdout = dup2(STDOUT_FILENO, 1001);
	int res = 0;

	piping(cmds, 0, &res, saved_stdin, saved_stdout);

	close(saved_stdin);
	close(saved_stdout);

	return (res);
}

/* 
//test

int main(void)
{
	char **cmds[4];

//	static char *cmd1[] = {"cat", NULL};
//    static char *cmd2[] = {"cat", NULL};
//    static char *cmd3[] = {"ls", "-l", NULL};

	static char *cmd1[] = {"ls", NULL};
    static char *cmd2[] = {"grep", "l", NULL};
    static char *cmd3[] = {"wc", NULL};//essayer commande inexistante (comme "wololo")

    cmds[0] = cmd1;
    cmds[1] = cmd2;
    cmds[2] = cmd3;
    cmds[3] = NULL;
	
	int res = picoshell(cmds);
	if (res)
		write(1, "Returned 1\n", 11);
	return (0);
} */