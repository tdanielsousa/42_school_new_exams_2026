/*
Assignment name		:	sandbox
Expected files		:	sandbox.c
Allowed functions	:	fork, waitpid, exit, alarm, sigaction, kill,
						printf, strsignal, errno
===============================================================================

Write the following function:

#include <stdbool.h>
int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)

This function must test if the function f is a nice function or a bad function,
you will return 1 if f is nice , 0 if f is bad or -1 in case of an error in
your function.

A function is considered bad if it is terminated or stopped by a signal
(segfault, abort...), if it exit with any other exit code than 0 or if it
times out.

If verbose is true, you must write the appropriate message among the following:

"Nice function!\n"
"Bad function: exited with code <exit_code>\n"
"Bad function: <signal description>\n"
"Bad function: timed out after <timeout> seconds\n"

You must not leak processes (even in zombie state, this will be checked using
wait).

We will test your code with very bad functions.
*/
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

void do_nothing(int sig)
{
	(void)sig;
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		alarm(timeout);
		/*un signal SIGALRM est envoyé au process appelant au bout de 'timeout' secondes.
		Par défaut, le processus se termine.
		Son code de retour est obtenu avec waitpid(pid, &st, 0).
		WIFSIGNALED(st) devient vrai. WTERMSIG(st) devient SIGALRM.
		*/
		f();
		exit(0);
	}
	/*Par défaut, alarm() affiche un message "alarm clock" (uniquement quand le processus est parent..), 
	donc on set un gestionnaire de signal pour SIGALRM (qui ne fait rien).
	Si 'sa.sa_handler = SIG_IGN', le signal est ignoré et aucune action n'est effectuée.
	Avec 'do_nothing', waitpid sera bien interrompu et retournera -1 avec errno == EINTR */
	struct sigaction sa;
	sa.sa_handler = do_nothing;
	/*sa.sa_mask est un masque de signaux qui spécifie les signaux à bloquer temporairement pendant l'exécution du gestionnaire de signal.
	Par défaut, sa.sa_mask n'est pas initialisé et peut contenir alors des valeurs aléatoires (qui baisent ton exam). Il faut alors le vider avec sigemptyset*/
	sigemptyset(&sa.sa_mask);
	/*sa.sa_flags = 0 garantit qu'aucune option n'est activé comme SA_RESTART qui peut s'activer par accident et n'interrompt pas waitpid*/
	sa.sa_flags = 0;
	sigaction(SIGALRM, &sa, NULL);

	/*La deuxième alarme (dans le parent) garantit que waitpid sera interrompu après timeout secondes si l'enfant
	ignore ou désactive son propre signal SIGALRM. (Comme cancel_alarm plus bas)*/
	alarm(timeout);

	int st;
	pid_t r = waitpid(pid, &st, 0);
	if (r == -1)
	{
		if (errno == EINTR)
		{
			/*Dès que waitpid est interrompu, il faut tuer le process enfant, sinon il deviendrait un process zombie et continuerait son exécution*/
			kill(pid, SIGKILL);
			waitpid(pid, NULL, 0);
			if (verbose)
				printf("Bad function: timed out after %d seconds\n", timeout);
			return (0);
		}
		return (-1);
	}
	if (WIFEXITED(st))
	{
		int ex_code = WEXITSTATUS(st);
		if (ex_code == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		printf("Bad function: exited with code %d\n", ex_code);
		return (0);
	}
	if (WIFSIGNALED(st))
	{
		if (WTERMSIG(st) == SIGALRM)
		{
			if (verbose)
				printf("Bad function: timed out after %d seconds\n", timeout);
			return (0);
		}
		if (verbose)
			printf("Bad function: %s\n", strsignal(WTERMSIG(st)));
		return (0);
	}
	return (-1);
}

void ok_f(void)
{
	printf("noice. ");
}

void inf_f(void)
{
	while (1)
		;
}

void bad_exit(void)
{
	exit(41);
}

void cancel_alarm(void)
{
	struct sigaction ca;
	ca.sa_handler = SIG_IGN;
	sigaction(SIGALRM, &ca, NULL);

	sleep(5);
	printf("f waited 5 seconds, should be terminated before by alarm set in parent process if timeout < 5\n");
}

void leak_f(void)
{
	int *p = NULL;
	*p = 4;
}

int main(void)
{
	//sandbox(bad_exit, 3, true);
	//sandbox(inf_f, 2, true);
	sandbox(cancel_alarm, 3, true);
}