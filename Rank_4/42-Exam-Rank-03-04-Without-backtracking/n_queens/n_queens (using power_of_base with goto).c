#include <stdlib.h>
#include <stdio.h>

int power_of_base(int base, int exponent)
{
	int power = 1;
	int i = 0;
	while (i < exponent)
	{
		power *= base;
		i++;
	}
	return power;
}

int main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	int columns[n];
	int diagonal_increasing[n * 2];
	int diagonal_decreasing[n * 2];
	int i = 0;
	while (i < power_of_base(n, n))
	{
		int j = 0;
		while (j < n)
		{
			columns[j] = 0;
			j++;
		}
		j = 0;
		while (j < n * 2)
		{
			diagonal_increasing[j] = 0;
			diagonal_decreasing[j] = 0;
			j++;
		}
		j = 0;
		while (j < n)
		{
			if (columns[i / power_of_base(n, j) % n] != 1)
				columns[i / power_of_base(n, j) % n] = 1;
			else
				goto next;
			if (diagonal_increasing[j - i / power_of_base(n, j) % n + n] != 1)
				diagonal_increasing[j - i / power_of_base(n, j) % n + n] = 1;
			else
				goto next;
			if (diagonal_decreasing[j + i / power_of_base(n, j) % n] != 1)
				diagonal_decreasing[j + i / power_of_base(n, j) % n] = 1;
			else
				goto next;
			j++;
		}
		j = 0;
		while (j < n)
		{
			printf("%d", i / power_of_base(n, j) % n);
			if (j != n - 1)
				printf(" ");
			j++;
		}
		printf("\n");
		next:
		i++;
	}
}