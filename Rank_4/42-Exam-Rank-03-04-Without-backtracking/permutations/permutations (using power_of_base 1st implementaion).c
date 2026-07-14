#include <stdio.h>

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return i;
}

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

int is_not_duplicated(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		int j = i + 1;
		while (str[j] != '\0')
		{
			if (str[i] == str[j])
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}

void sort(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		int j = 0;
		while (str[j] != '\0')
		{
			if (str[i] < str[j])
			{
				char tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
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
	sort(argv[1]);
	char array[n];
	array[n] = '\0';
	int i = 0;
	while (i < power_of_base(n, n))
	{
		int j = 0;
		while (j < n)
		{
			array[n - j - 1] = argv[1][i / power_of_base(n, j) % n];
			j++;
		}
		if (is_not_duplicated(array))
			puts(array);
		i++;
	}
}
