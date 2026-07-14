#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int picoshell(char **cmds[])
{
    int i = 0;
    int res = 0;
    pid_t pid;
    pid_t child_pid[128];
    int child_count = 0;
    int prev_read_fd = -1;
    int fds[2];

    while (cmds[i])
    {
        if (cmds[i + 1] && pipe(fds) == -1)
            return 1;
        pid = fork();
        if (pid == -1)
            return 1;
        if (pid == 0)
        {
            if (prev_read_fd != -1)
            {
                dup2(prev_read_fd, 0);
                close(prev_read_fd);
            }
            if (cmds[i + 1])
            {
                dup2(fds[1], 1);
                close(fds[1]);
                close(fds[0]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        child_pid[child_count++] = pid;
        if (prev_read_fd != -1) close(prev_read_fd);
        if (cmds[i + 1])
        {
            close(fds[1]);
            prev_read_fd = fds[0];
        }
        i++;
    }
    int j, status;
    for (j = 0; j < child_count; j++)
    {
        if (waitpid(child_pid[j], &status, 0) == -1)    return 1;
        else if (WIFEXITED(status) && WEXITSTATUS(status))
            res = 1;
    }
    return res;
}


int main()
{
    char *cmd1[] =  {"ls", "-la", NULL};
    char *cmd2[] =  {"grep", ".c", NULL};
    char *cmd3[] =  {"wc", "-l", NULL};
    char **cmds[] = { cmd1, cmd2, cmd3, NULL };

	if (picoshell(cmds))
        return printf("failllled\n"), 1;
    return 0;
}