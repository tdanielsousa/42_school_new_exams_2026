#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
problem (similar to leetcode n78.Subsets)
display all subsets of a set whose sum of its elements is equal to the first argument.
The numbers of the set are from the second argument to the last.
A subset must not be displayed a second time.

exemple1)
./a.out 5 2 3 | cat -e
2 3$

ex2)
./a.out 12 5 7 4 3 2 | cat -e
5 7$
5 4 3$
7 3 2$
*/

int	somme_subset(char **nbs)
{
	int res = 0;
	int i = 0;

	while (nbs[i])
	{
		res += atoi(nbs[i]);
		i++;
	}
	return (res);
}

void	print_subset(char **subset)
{
	int i = 0;

	while (subset[i])
	{
		fprintf(stdout, "%s", subset[i]);
		if (subset[i + 1])
			fprintf(stdout, " ");
		i++;
	}
}

void	printpowerset(char **nbs, int the_sum, int n_nbs)
{
	int n_subset = 1 << n_nbs;//2^n_nbs
	int i = 0;
	int j;
	int k;
	char **subset = calloc(n_nbs + 1, sizeof(char *));

	while (i < n_subset)
	{
		j = 0;
		k = 0;
		while (j < n_nbs)
		{
			if (i & (1 << j))
			{
				subset[k] = nbs[j];
				k++;
			}
			j++;
		}
		subset[k] = NULL;
		if (somme_subset(subset) == the_sum)
		{
			print_subset(subset);
			fprintf(stdout, "\n");
		}
		i++;
	}
	free(subset);
}

int main(int argc, char **argv)
{
	if (argc <= 2)
		return (0);
	
	int the_sum = atoi(argv[1]);
	
	printpowerset(argv + 2, the_sum, argc - 2);
	return (0);
}