#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void print_set(int *tab, int size)
{
    int i = 0;
    while (i < size)
    {
        printf("%d", tab[i]);
        i++;
    if ( i < size)
            printf(" ");
    }
    printf("\n");
}

void find_subsets(int *tab, int size, int target, int index, int *subset, int subset_size, int current_sum)
{
    if (index == size)
    {
        if (current_sum == target)
            print_set(subset, subset_size);
        return;
    }

    find_subsets(tab, size, target, index + 1, subset, subset_size, current_sum);
    
    subset[subset_size] = tab[index];
    find_subsets(tab, size, target, index + 1, subset, subset_size + 1, current_sum + tab[index]);
}

void powerset(int *tab, int size, int target)
{
    int *subset = malloc(sizeof(int) * size);
    find_subsets(tab, size, target, 0, subset, 0, 0);
    free(subset);
}

int main(int ac, char **av)
{
    if (ac < 3)
        return 1;

    int target = atoi(av[1]);
    int n = ac - 2;

    int *tab = malloc(sizeof(int) * n);
    int i = 0;
    while (i < n)
    {
        tab[i] = atoi(av[i + 2]);
        i++;
    }

    powerset(tab, n, target);
    free(tab);

    return 0;
}