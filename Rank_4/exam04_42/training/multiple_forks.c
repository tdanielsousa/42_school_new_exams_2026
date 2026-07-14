#include <stdio.h>
#include <unistd.h>

/*
 * Formula: 2^n processes where n is the number of forks. 
*/
int main()
{
    fork(); // creates 2 processes
    fork(); // each of those 2 creates another = 4 processes
    fork(); // each of those 4 creates another = 8 processes

    printf("Hello\n");
    return 0;
}