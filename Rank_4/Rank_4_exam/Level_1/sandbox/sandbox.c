#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int sandbox(void (*f)(void), unsigned int t, bool v)
{
	pid_t child = fork();
	if (child < 0) return -1;

	if (child == 0) { f(); exit(0); }

	pid_t killer = fork();
	if (killer < 0) return -1;

	if (killer == 0)
	{
		sleep(t);
		kill(child, SIGKILL);
		exit(0);
	}

	int st;
	waitpid(child, &st, 0);
	kill(killer, SIGKILL);
	waitpid(killer, 0, 0);

	if (WIFEXITED(st))
	{
		int c = WEXITSTATUS(st);
		if (c == 0){ if (v) printf("Nice function!\n"); return 1; }
		if (v) printf("Bad function: exited with code %d\n", c);
		return 0;
	}
	if (WIFSIGNALED(st))
	{
		int s = WTERMSIG(st);
		if (s == SIGKILL)
			{ if (v) printf("Bad function: timed out after %u seconds\n", t); }
		else if (v)
			printf("Bad function: %s\n", strsignal(s));
		return 0;
	}
	return -1;
}

// TEST MAIN:    --------------------------------------------------------------------

void good(void){}
void bad_exit(void){ _exit(5); }
void bad_sig(void){ int *p = 0; *p = 1; }
void bad_loop(void){ while(1); }

int main(void)
{
	sandbox(good, 1, 1);
	sandbox(bad_exit, 1, 1);
	sandbox(bad_sig, 1, 1);
	sandbox(bad_loop, 1, 1);
}
