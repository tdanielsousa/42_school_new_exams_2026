#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
problem: (leetcode n.46 permutations)
display all permutations of characters for a set given as argv[1], in the alphabetical order
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

int get_factoriel(int n)
{
    int res = 1;
    
    while (n > 0)
    {
        res = res * n;
        n--;
    }
    return (res);
}

int ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

void	ft_swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

char	*ft_strdup(char *s)
{
	char *res = calloc(ft_strlen(s) + 1, sizeof(char));
	int i = -1;

	while (s[++i])
		res[i] = s[i];
	return (res);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

void	permute(char *set, int counter, int total, char **permuts, int *index)
{
	if (counter == total)
	{
		permuts[*index] = ft_strdup(set);
		(*index)++;
		return ;
	}
	int i = counter;
	while (i < total)
	{
		ft_swap(set + counter, set + i);
		permute(set, counter + 1, total, permuts, index);
		ft_swap(set + counter, set + i);
		i++;
	}
}

void	print_2darray_and_free(char **tab, int n)
{
	int i = 0;

	while (tab[i])
	{
		write(1, tab[i], n);
		write(1, "\n", 1);
		free(tab[i]);
		i++;
	}
}

void	sort_strings(char **tab)
{
	char *tmp;
	int i = 0;
	int sorted = 0;

	while (!sorted) 
	{
		sorted = 1;
		i = 0;
		while (tab[i + 1])
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

int main(int argc, char **argv)
{
    if (argc <= 1)
        return (0);

	int n_elems = ft_strlen(argv[1]);
	char *set = ft_strdup(argv[1]);
	int i = -1;
	char **permuts = calloc(get_factoriel(n_elems) + 1, sizeof(char *));
	int index = 0;

	permute(set, 0, n_elems, permuts, &index);
	permuts[index] = NULL;
	sort_strings(permuts);
	print_2darray_and_free(permuts, n_elems);
	free(permuts);
	free(set);
    return (0);
}
/*
problem:
display all permutations of characters for a set given as argv[1], in the alphabetical order
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