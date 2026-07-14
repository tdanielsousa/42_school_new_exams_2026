#include <stdlib.h>
#include <stdio.h>

int power_of_2(int exponent)
{
	int i = 0;
	int power = 1;
	while (i < exponent)
	{
		power *= 2;
		i++;
	}
	return power;
}

int main(int argc, char **argv)
{
	int i = 0;
	while (i < power_of_2(argc - 2))
	{
		int j = 0;
		int sum = 0;
		int solutions1 = 0;
		while (j < argc - 2)
		{
			sum += (i / power_of_2(j) % 2) * atoi(argv[j + 2]);
			solutions1 += i / power_of_2(j) % 2;
			j++;
		}
		if (atoi(argv[1]) == sum)
		{
			j = 0;
			int solutions2 = 0;
			while (j < argc - 2)
			{
				if (i / power_of_2(j) % 2)
				{
					printf("%s", argv[j + 2]);
					solutions2++;
					if (solutions1 != solutions2)
						printf(" ");
				}
				j++;
			}
			printf("\n");
		}
		i++;
	}
}
