#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

//parsing not done
int	solve(char *s, int *i)
{
	int nums[500];
	int count = 0;
	int nb = 0;
	char op = '+';

	while (s[*i] && s[*i] != ')')
	{
		if (isdigit(s[*i]))
			nb = s[*i] - '0';
		else if (s[*i] == '(')
		{
			(*i)++;
			nb = solve(s, i);
		}

		if (op == '+')
			nums[count++] = nb;
		else if (op == '*')
			nums[count - 1] *= nb;
		
		op = s[*i];
		if (s[*i] != '\0' && s[*i] != ')')
			(*i)++;
	}
	if (s[*i] == ')')
		(*i)++;

	int k = 0;
	int res = 0;
	while (k < count)
	{
		res += nums[k];
		k++;
	}
	return (res);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	int i = 0;
	printf("%d\n", solve(argv[1], &i));
	return (0);
}