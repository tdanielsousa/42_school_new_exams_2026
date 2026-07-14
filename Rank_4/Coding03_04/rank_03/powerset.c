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

int tab_somme(int *tab, int size)
{
	int i = -1;
	int res = 0;

	while (++i < size)
		res = res + tab[i];
	return (res);
}

void print_subset(int *tab, int size)
{
	int i = 0;
	
	while (i < size)
	{
		fprintf(stdout, "%d", tab[i]);
		if (i < size - 1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
}

void	printpowerset(int the_sum, int *set, int n_elem)
{
	int n_subsets = 1 << n_elem;
	int i_subs = 0;
	int *res = calloc(n_elem, sizeof(int));
	int j_res;
	int k_set;
	int shifter;

	while (i_subs < n_subsets)
	{
		k_set = n_elem - 1;
		shifter = 0;
		j_res = 0;
		while (k_set >= 0)
		{
			if (1 & (i_subs >> shifter))
			{
				res[j_res] = set[k_set];
				j_res++;
			}
			k_set--;
			shifter++;
		}
		if (tab_somme(res, j_res) == the_sum)
			print_subset(res, j_res);
		i_subs++;
	}
	free(res);
}

int main(int argc, char **argv)
{
	if (argc <= 2)
		return (0);

	int the_sum = atoi(argv[1]);
	int n_elem = argc - 2;
	int set[n_elem];
	int i = -1;

	while (++i < n_elem)
		set[i] = atoi(argv[2 + i]);

	printpowerset(the_sum, set, n_elem);
	
	return (0);
}
