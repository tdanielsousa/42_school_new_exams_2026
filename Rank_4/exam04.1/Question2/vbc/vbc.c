

node	*parse_expr(char **s)
{
	node *left = parse_term(s);
	while (accept(s, '+'))
	{
		node *right = parse_term(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		node n = {ADD, 0, left, right};
		left = new_node(n);
	}
	return (left);
}

node	*parse_term(char **s)
{
	node *left = parse_factor(s);
	while (accept(s, '*'))
	{
		node *right = parse_factor(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		node n = {MULTI, 0, left, right};
		left = new_node(n);
	}
	return (left);
}

node	*parse_factor(char **s)
{
	if (accept(s, '('))
	{
		node *n = parse_expr(s);
		if (!expect(s, ')'))
		{
			destroy_tree(n);
			return (NULL);
		}
		return (n);
	}
	if (is_digit(**s))
	{
		node l = {VAL, **s - '0', NULL, NULL}
		(*s)++;
		return (new_node(l));
	}
	unexpected(**s);
	return (NULL);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	char input = av[1];
	node *tree = parse_expr(&input);
	if (!tree)
		return (1);
	if (*input)
	{
		unexpected(*input);
		destroy_tree(tree);
		return (1);
	}
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0);
}
