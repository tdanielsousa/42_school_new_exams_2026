#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    int status;

    if (pid == 0)
        return 1337; // the max number is 256, so 1337 % 256 = 57
    else {
        wait(&status);
        if (WIFEXITED(status))
            printf("child exited with code %d\n", WEXITSTATUS(status));
    }
    return 0;
}