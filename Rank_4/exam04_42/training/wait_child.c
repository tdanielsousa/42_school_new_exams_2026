# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    
    if (pid == 0)
    {
        printf("Child working...\n");
        sleep(2);
        printf("Child done\n");
        return 42;
    }
    else 
    {
        int status;
        printf("Parent waiting...\n");
        wait(&status);  // wait for child to finish
        if (WIFEXITED(status))
        {
            printf("Child exited with status %d \n", WEXITSTATUS(status));
        }
    }
    return 0;
}