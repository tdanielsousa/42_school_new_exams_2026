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
	char board[n][n];
	int columns[n];
	int diagonal_increasing[n * 2];
	int diagonal_decreasing[n * 2];
	int i = 0;
	while (i < power_of_base(n, n))
	{
		//	reseting board
		int ii = 0;
		while (ii < n)
		{
			int jj = 0;
			while (jj < n)
			{
				board[ii][jj] = '.';
				jj++;
			}
			ii++;
		}
		//	reseting columns
		int j = 0;
		while (j < n)
		{
			columns[j] = 0;
			j++;
		}
		//	reseting diagonals
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
			board[j][i / power_of_base(n, j) % n] = 'Q';
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
		//	printing board
		ii = 0;
		while (ii < n)
		{
			int jj = 0;
			while (jj < n)
			{
				printf("%c ", board[ii][jj]);
				jj++;
			}
			printf("\n");
			ii++;
		}
		printf("\n");
		next:
		i++;
	}
}