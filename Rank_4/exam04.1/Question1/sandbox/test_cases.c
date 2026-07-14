#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	sandbox(void (*f)(void), unsigned int timeout, int verbose);

/* Nice function */
void	nice_function(void)
{
	printf("\n1. Hello from nice_function!\n");
}

/* Causes segmentation fault */
void	segfault_function(void)
{
	printf("\n2. Segfault function\n");
	int	*ptr = NULL;
	*ptr = 42;
}

/* Runs forever */
void	infinite_loop(void)
{
	printf("\n3. Infinite loop function\n");
	while (1) {}
}

/* Exits with error code 42 */
void	exit_with_error(void)
{
	printf("\n4. Exit_with_error function\n");
	exit(42);
}

void segfault_function_2(void) 
{
	printf("\n5. Segfault function\n");
	*(char *)0 = 0;
}

void abnormal_termination(void) 
{
	printf("\n6. Abnormal termination function\n");
	abort();
}

int	main()
{
	sandbox(nice_function, 2, 1);
	sandbox(exit_with_error, 2, 1);
	sandbox(segfault_function, 2, 1);
	sandbox(infinite_loop, 2, 1);
	sandbox(segfault_function_2, 5, 1);
	sandbox(abnormal_termination, 2, 1);
	sandbox(nice_function, 2, 0);
	return (0);
}