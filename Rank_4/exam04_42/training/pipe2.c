#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

void main()
{
    int fds[2];
    int pid;
    char msg[] = "this msg form parent";
    char buffer[50];

    if (pipe(fds) == -1)
    {
        printf("pipe failed\n"); 
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        printf("fork failed\n");
        return;
    }

    if (pid == 0)   // child process
    {
        close(fds[1]); // close write end
        read(fds[0], buffer, strlen(msg));
        printf("buffer = %s\n", buffer);
        close(fds[0]);
    }
    else { // parent process
        close(fds[0]); // close read end
        write(fds[1], msg, strlen(msg));
        close(fds[1]);
    }

}