# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <ctype.h>

const char *input;
int pos;
int faut;

int addition();
int parentheses()
{
    if (input[pos] == 0)
    {
        printf("Unexpected end of input\n");
        faut = 1;
    }
    if (faut)
        return 1;
    if (isdigit(input[pos]))
    {
        int data = input[pos] - 48;
        pos++;
        return data;
    }
    if (input[pos] == '(')
    {
        pos++;
        int p = addition();
        if (input[pos] != ')')
        {
            if (input[pos] == 0)
            {
                printf("Unexpected end of input\n");
                faut = 1;
            }
            else
            {
                printf("Unexpected token '%c'\n", input[pos]);
                faut = 1;   
            }
            return 1;
        }
        pos++;
        return p;
    }
    printf("Unexpected token '%c'\n", input[pos]);
    faut = 1;
    return 1;
}

int multiplication()
{
    int data = parentheses();
    if (faut)
        return 1;
    while (input[pos] == '*')
    {
        pos++;
        data *= parentheses();
        if (faut)   
            return 1;
        
    }
    return data;
}

int addition()
{
    int data = multiplication();
    if (faut)
        return 1;
    while (input[pos] == '+')
    {
        pos++;
        data += multiplication();
        if (faut)
            return 1;
        
    }
    return data;
}

int main (int ac, char **av)
{
    if (ac != 2)
        return 1;
    input = av[1];
    int result = addition();
    if (faut)
        return 1;
    if (input[pos])
    {
        printf("Unexpected token '%c'\n", input[pos]);
        return 1;
    }
    printf("%d\n", result);
}
