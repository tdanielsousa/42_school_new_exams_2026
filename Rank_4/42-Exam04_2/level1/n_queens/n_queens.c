#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int is_safe(int *tab, int col, int row)
{
    for(int i = 0; i < col; i++)
    {
        if(tab[i] == row || abs(i - col) == abs(tab[i] - row))
            return 0;
    }
    return 1;
}

void solve(int *tab, int n, int col)
{
    if(col == n)
    {
        for(int i = 0; i < n; i++)
        {
            printf("%d",tab[i]);
            if(i < n - 1)
                printf(" ");
        }
        printf("\n");
        return ;
    }
    for(int i= 0; i < n; i++)
    {
        if(is_safe(tab , col , i))
        {
            tab[col] = i;
            solve(tab, n, col + 1);
        }
    }
}

int main(int ac , char **argv)
{
    if(ac != 2)
        return 0;
    int n = atoi(argv[1]);
    int *tab = calloc(sizeof(int) , n);
    solve(tab ,n,0);
    return 0;
}