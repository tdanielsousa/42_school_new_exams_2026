#include <stdio.h>
#include <ctype.h>

int unexpected_digit(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (isdigit(str[i]) && isdigit(str[i - 1]))
			return 1;
		i++;
	}
	return 0;
}

char get_digit(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (isdigit(str[i]) && isdigit(str[i - 1]))
			return str[i];
		i++;
	}
	return 0;
}

int is_not_balanced(char *str)
{
	int i = 0;
	int balance = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			balance++;
		if (str[i] == ')')
			balance--;
		if (balance < 0)
			return 2;
		i++;
	}
	if (balance == 0)
		return 0;
	return 1;
}

int unexpected_end(char *str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] == '+' || str[i - 1] == '*')
		return 1;
	return 0;
}

int idx = 0;

int eval_expr(char *exp);
int eval_term(char *exp);
int eval_factor(char *exp);

int eval_expr(char *exp)
{
	int result = eval_term(exp);
	while (exp[idx] == '+')
	{
		idx++;
		result += eval_term(exp);
	}
	return result;
}

int eval_term(char *exp)
{
	int result = eval_factor(exp);
	while (exp[idx] == '*')
	{
		idx++;
		result *= eval_factor(exp);
	}
	return result;
}

int eval_factor(char *exp)
{
	int result;
	if (exp[idx] == '(')
	{
		idx++;
		result = eval_expr(exp);
	}
	if (exp[idx] == ')')
		idx++;
	else if (isdigit(exp[idx]))
	{
		result = exp[idx] - '0';
		idx++;
	}
	return result;
}

int main(int argc, char **argv)
{
	(void)argc;
	if (unexpected_digit(argv[1]))
	{
		printf("Unexpected token '%c'\n", get_digit(argv[1]));
		return 1;
	}
	if (is_not_balanced(argv[1]))
	{
		if (is_not_balanced(argv[1]) == 1)
			printf("Unexpected token '('\n");
		if (is_not_balanced(argv[1]) == 2)
			printf("Unexpected token ')'\n");
		return 1;
	}
	if (unexpected_end(argv[1]))
	{
		printf("Unexpected end of input\n");
		return 1;
	}
	printf("%d\n", eval_expr(argv[1]));
}
