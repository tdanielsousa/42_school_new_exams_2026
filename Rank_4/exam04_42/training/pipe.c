#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


/*
 * a pipe is a unidirectional communication channel used to allow data transfer between processes — typically between a parent and child process.
 * prototype: int pipe(int fd[2]);
 * return 0 on success, -1 on failure -> fd[0] = read end, fd[1] = write end
 *
   ⚙️ Typical usage flow:
    1. Create a pipe using pipe(fd).
    2. Call fork() to create a child process.
    3. Parent and child close unused ends:
        - Writer closes read end (close(fd[0]))
        - Reader closes write end (close(fd[1]))
    4. Communicate using write() and read().
 * 
 */
void main()
{
    // one 0 fd for reading  and 1 fd for writing
    int pipefds[2];
    char buffer[256] = {0};

    printf("parent pid: %d\n", getpid());
    pipe(pipefds);
    write(pipefds[1], "hello", 5);
    
    if (fork() < 0)
        return;
    
    read(pipefds[0], buffer, 5);

    printf("got from pipe: %s\n", buffer);
    printf("child pid: %d\n", getpid());
}