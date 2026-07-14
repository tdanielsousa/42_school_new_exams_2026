#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int pid;
    printf("Before fork %d\n", getpid());
    pid = fork(); // create child process
    if (pid == -1)
        return printf("fork failed"), 1;
    if (pid == 0)
    {
        // executed by child process
        printf("child process: My pid is %d, the parent's pid is %d\n", getpid(), getppid());
    }
    else 
    {
        // executed by parent process
        printf("Parent process: My process is %d, the child's pid is %d\n", getpid(), pid);
    }
    printf("After fork(), both processes continue here. PID: %d\n", getpid());

    printf("second test ################### second test\n");

    int fd = open("file.txt", O_CREAT | O_WRONLY, 0644);
    int pid2 = fork();
    if (fd < 0) return printf("fd creation failed\n"), 1;
    if (pid2 == 0)
        write(fd, "from child\n", 11);
    else
        write(fd, "from parent\n", 12);
    close(fd);
    return 0;
}