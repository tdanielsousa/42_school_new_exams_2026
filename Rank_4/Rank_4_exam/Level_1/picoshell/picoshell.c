#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	picoshell(char **cmds[])
{
	int i = 0, fd[2], in, pid;

	while (cmds[i])                       //  processing every command(cmd)
	{
		if (cmds[i + 1] && pipe(fd) == -1)    //if there's another cmd --> create a Pipe
			return (1);					     //if it is the last — we don't need no pipe
		pid = fork();   //  create a child 👶  
		if (pid == -1)
			return (1);
		if (pid == 0)     //👶
		{
			if (in != 0)    // if not a First cmd
			{
				dup2(in, 0);  // previous Pipe to Stdin
				close(in);
			}
			if (cmds[i + 1])   // if not a last cmd
			{
				close(fd[0]);
				dup2(fd[1], 1);   // write Stdout to a Pipe
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);    // launch a cmd
			exit(1);
		}
		if (in != 0)      // close old end of a pipe
			close(in);
		if (cmds[i + 1])   // making a new pipe for next cmd
		{
			close(fd[1]);
			in = fd[0];
		}
		i++;    // cmd1 --> cmd2...
	}
	while (i-- > 0)   // wait...
		wait(NULL);
	return (0);
}

																							

//MAIN for a test:   ------------------------------------------------------------------------
int main(void)
{
    char *cmd1[] = {"echo", "hello world", NULL};
    char *cmd2[] = {"grep", "hello", NULL};
    char *cmd3[] = {"wc", "-c", NULL};

    char **cmds[] = {cmd1, cmd2, cmd3, NULL};

    if (picoshell(cmds) == 1)
        return (1);
    return (0);
}