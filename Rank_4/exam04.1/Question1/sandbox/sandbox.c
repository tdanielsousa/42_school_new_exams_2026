#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

static volatile sig_atomic_t timeout_flag = 0;

// Signal handler for SIGALRM
void	handle_alarm(int sig)
{
	(void)sig;
	timeout_flag = 1;
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t				cpid; // A variable to store the child process ID.
	struct sigaction 	sa;  // A variable to configure the signal handler.
	int					status; // A variable where the exit status of the child will be stored.
	pid_t				ret; // A variable to store the return value from wa.
	int 				exit_code;
	
	sa.sa_handler = handle_alarm; // Setup signal handling for timeout
	sigemptyset(&sa.sa_mask);  // Initialize sa_mask to an empty signal set (no signals are blocked during signal handling).
	sa.sa_flags = 0;  // Set signal handler flags to 0 (default behavior).
	if (sigaction(SIGALRM, &sa, NULL) == -1) // Set up the signal handler for SIGALRM. If it fails, handle the error.
	{
		return (-1);
	}

	cpid = fork();
	if (cpid == -1)
	{
		return (-1);
	}
	if (cpid == 0) // Child process
	{
		f();
		exit(0);
	}
	alarm(timeout);
	while (1)
	{
		ret = waitpid(cpid, &status, 0);
		if (ret == cpid) // Checks if waitpid() successfully returned and that it returned the child PID
		{
			if (WIFEXITED(status)) // Case 1: the child exited normally (e.g., return 0;).
			{
				exit_code = WEXITSTATUS(status);
				if (exit_code == 0) // Case 1.1: Child terminated with 0 exit code
				{
					if(verbose)
						printf("Nice function\n");
					return (0);
				}
				else // Case 1.2: Child terminated with non-zero exit code
				{
					if (verbose)
						printf("Bad function: exited with code %d\n", exit_code);
					return (1);
				}
			}
			else if (WIFSIGNALED(status)) // Case 2: Child was killed by a signal
			{
				if (verbose)
					printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
				return (0);
			}
		} 
		else if (timeout_flag) // Case 3: Timeout occurred
		{
			kill(cpid, SIGKILL); // Kill child process
			waitpid(cpid, &status, 0); // Clean up zombie process
			if (verbose)
				printf("Bad funciton: timed out after %d seconds\n", timeout);
			return(0);
		}
		usleep(1000);
	}
	return (-1);
}
