#include <unistd.h>

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return i;
}

int power_of_base(int base, int exponent)
{
	int i = 0;
	int power = 1;
	while (i < exponent)
	{
		power *= base;
		i++;
	}
	return power;
}

int is_not_duplicated(int *array, int size)
{
	int i = 0;
	while (i < size)
	{
		int j = i + 1;
		while (j < size)
		{
			if (array[i] == array[j])
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}

void sort(char *array, int size)
{
	int i = 0;
	while (i < size)
	{
		int j = i + 1;
		while (j < size)
		{
			if (array[i] > array[j])
			{
				char tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 0;
	int n = ft_strlen(argv[1]);
	sort(argv[1], n);
	int array[n];
	int i = 0;
	while (i < power_of_base(n, n))
	{
		int j = 0;
		while (j < n)
		{
			array[n - j - 1] = i / power_of_base(n, j) % n;
			j++;
		}
		if (is_not_duplicated(array, n))
		{
			j = 0;
			while (j < n)
			{
				write(1, &argv[1][array[j]], 1);
				j++;
			}
			write(1, "\n", 1);
		}
		i++;
	}
}
