#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * exevp() is one of the exec family functions used to run another program
   by replacing the current process image with a new one.
 * prototype: int execv(const char *path, char *const argv[]);
    - path: the full path to the executable(e.g., "/bin/ls")
    - argv: array of strings(arguments), ending with NULL
 * Return value:
    - i never returns in succesfull
    - return -1 on error(and sets errno)
 * Important facts about it:
    - it doesn't create a new process, it transforms the current one,
 * what happens step by step:
    1. fork() creates a child process
    2. the child calls execv("/bin/ls", args)
        -> the child process is replaces with /bin/ls
    3. the parent process waits using wait()
    4. when ls finishes, control return the parent

*/
int main()
{
    int pid = fork();

    char *const args[] = {"ls", "-la", "/home/", NULL};
    if (pid == 0)
    {
        execvp("ls", args); // doesn't need the full path like execv
        perror("execv failed");
    }
    else {
        printf("wait %s to execute in the child process\n\n", args[0]);
        wait(NULL);
        printf("\nthe command executed in the child\n");
    }
    return 0;
}