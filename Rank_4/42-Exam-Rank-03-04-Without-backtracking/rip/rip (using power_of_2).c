#include <stdio.h>

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return i;
}

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

int is_balanced(char *str)
{
	int balance = 0;
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			balance++;
		if (str[i] == ')')
			balance--;
		if (balance < 0)
			return 0;
		i++;
	}
	if (balance == 0)
		return 1;
	return 0;
}

void inside(char *argv1, int *min, int step)
{
	int len = ft_strlen(argv1);
	char array[len + 1];
	array[len] = '\0';
	int i = 0;
	while (i < power_of_2(len))
	{
		int spaces_nbr = 0;
		int j = 0;
		while (argv1[j] != '\0')
		{
			array[j] = argv1[j];
			j++;
		}
		j = 0;
		while (j < len)
		{
			if (i / power_of_2(j) % 2)
			{
				array[j] = ' ';
				spaces_nbr++;
			}
			j++;
		}
		if (step == 1 && is_balanced(array) && spaces_nbr < *min)
			*min = spaces_nbr;
		if (step == 2 && is_balanced(array) && spaces_nbr == *min)
			puts(array);
		i++;
	}
}

int main(int argc, char **argv)
{
	int min = ft_strlen(argv[1]);
	inside(argv[1], &min, 1);
	inside(argv[1], &min, 2);
}
