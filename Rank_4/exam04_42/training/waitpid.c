#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> // waitpid
#include <sys/wait.h> // waitpid

/*
 * waitpid() is more powerful and flexible version of wait()
    ✔️ Wait for a specific child
    ✔️ Control how it waits (block, non-block, etc.)
    ✔️ Get detailed info about child termination (like wait())
 * prototype: pid_t waitpid(pid_t pid, int *status, int options);
    - pid: which child to wait for
    - status: pointer to store child exit info(or NULL)
    - options: control wait behavior
 * choices for pid:
    - > 0: waits for that specific child PID
    - 0: wait for any child in the same process group
    - -1: waits for any child process(same as wait())
    - < -1: waits for any child in process group
 * common options values:
    - 0: default(block until child finishes)
    - WHOHANG: don't block, retun immediately if no child exits
 * return value: 
    - > 0: the PID of the child that was waited for
    - 0: No child exited(only if WHOHANG used)
    - -1: Error(e.g., no such child)
 */
int main()
{
    pid_t pid = fork();
    int status;

    if (pid == 0)
        return ( printf("child: running\n"),sleep(2), 42 );
    else {
        printf("wait for child to complete\n");
        waitpid(pid, &status, 0);
        printf("child process finishes with the exit code %d\n", WEXITSTATUS(status));
    }

}