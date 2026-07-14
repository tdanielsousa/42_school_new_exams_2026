#include <sys/types.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <stdio.h>

/*
 * wait() is a syscall used by parent process to wait for one of its chils process to terminate.
 * When a child process finishes, it does not disappear immediately. Instead, it becomes a zombie process until the parent reads its exit status using wait().
  ✔️ Without wait(), the child becomes a zombie (dead but still consuming a slot in process table)
  ✔️ wait() cleans up that zombie and frees resources
  ✔️ It allows the parent to synchronize with the child (i.e., wait until it finishes before continuing)
  * Return of wait: PID>0 -> PID of child that terminated
                    -1 -> ERROR(e.g., no child exists)
  * prototype: pid_t wait(int *status);
    * status: status is a pointer that lets you know how the child ended (normally? crashed? signaled?)
        - If you don’t care, you can pass NULL.
        - You can use macros like WIFEXITED(status) and WEXITSTATUS(status) to interpret it.
  */

int main()
{
    pid_t pid = fork();
    
    if (pid == 0) {
        printf("Child: I'm finishing now.\n");
    }
    else {
        wait(NULL); // wait for the child to finish(order is predictable now)
        printf("Parent: child has finished, I can continue now.\n");
    }   

    return 0;
}