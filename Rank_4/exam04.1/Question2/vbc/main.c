#include "vbc.h"

node	*pars_expr(char **s);

node	*new_node(node n)
{
	node *ret = calloc(1, sizeof(node));
	if (!ret)
		return NULL;
	*ret = n;
	return ret;
}

void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

int	accept(char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		return 1;
	}
	return 0;
}

int	expect(char **s, char c)
{
	if (accept(s, c))
		return 1;
	unexpected(**s);
		return 0;
}

int	eval_tree(node *tree)
{
	switch (tree->type)
	{
		case ADD:
			return (eval_tree(tree->l) + eval_tree(tree->r));
		case MULTI:
			return (eval_tree(tree->l) * eval_tree(tree->r));
		case VAL:
			return tree->val;
	}
	return 0;
}

void destroy_tree(node* tree)
{
    if (tree) {
        if (tree->type != VAL) {
            destroy_tree(tree->l);
            destroy_tree(tree->r);
        }
        free(tree);
    }
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	char *input = av[1];
	node *tree = pars_expr(&input);
	if (!tree)
		return 1;
	else if (*input) // 3.
	{
		printf("it's not the end of the expression: %c\n", *input);
		unexpected(*input);
		destroy_tree(tree);
		return 1;
	}
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
}
