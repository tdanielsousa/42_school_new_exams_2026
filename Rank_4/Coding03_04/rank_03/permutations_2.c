
#include <stdlib.h>
#include <stdbool.h>

/*
problem: (leetcode n.46 permutations)
display all permutations of characters for a set given as argv[1], in the alphabetical order.

In the exam, printf is not allowed. Use write.
exemple1)
./a.out po
op
po

exemple2)
./a.out cba
abc
acb
bac
bca
cab
cba
*/

int my_strlen(char *s)
{
	if (!s)
		return (0);

	int i = 0;

	while (s[i])
		i++;
	return (i);
}

int facto(int size)
{
	int res = 1;

	while (size > 1)
	{
		res = res * size;
		size--;
	}
	return (res);
}

char *my_strdup(char *s)
{
	int i = -1;
	char *res = malloc(sizeof(char) * (my_strlen(s) + 1));

	while (s[++i])
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}

void	permute(char *set, char **res, int *index_res, char *run, int *j_run, bool *used)
{
	if (*j_run == my_strlen(set))
	{
		res[*index_res] = my_strdup(run);
		(*index_res)++;
		return ;
	}
	int k_set = 0;
	while (k_set < my_strlen(set))
	{
		if (!used[k_set])
		{
			used[k_set] = true;
			run[*j_run] = set[k_set];
			(*j_run)++;
			permute(set, res, index_res, run, j_run, used);
			used[k_set] = false;
			(*j_run)--;
		}
		k_set++;
	}
}

char **permutations(char *set)
{
	int n = my_strlen(set);
	char **res = malloc(sizeof(char *) * (facto(n) + 1));
	int index_res = 0;

	char *run = calloc(sizeof(char), n + 1);
	int j_run = 0;

	bool *used = malloc(sizeof(bool) * n);
	int i = -1;
	while (++i < n)
		used[i] = false;

	permute(set, res, &index_res, run, &j_run, used);
	res[index_res] = NULL;
	free(run);
	free(used);

	return (res);
}

char *sort_str(char *str)
{
	char *res = my_strdup(str);
	int i = 0;
	char tmp;
	
	while (i < my_strlen(str) - 1)
	{
		if (res[i] > res[i + 1])
		{
			tmp = res[i];
			res[i] = res[i + 1];
			res[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	return (res);
}

#include <stdio.h>
int main(int argc, char **argv)
{
	if (argc <= 1)
		return (0);

	char *set = sort_str(argv[1]);
//	printf("sorted argv[1]: %s\n\n", set);

	char **res = permutations(set);
	int i = -1;
	
	while (res[++i])
		printf("%s\n", res[i]);

	i = -1;
	while (res[++i])
		free(res[i]);
	free(res);
	free(set);
	return (0);
}
