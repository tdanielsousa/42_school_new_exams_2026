#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
	enum
	{
		ADD,
		MULTI,
		VAL
	} type;
	int val;
	struct node *l;
	struct node *r;
} node;

node *create_addition_tree(char **s);

node *new_node(node n)
{
	node *ret = calloc(1, sizeof(n));
	if (!ret)
		return (NULL);
	*ret = n;
	return (ret);
}

void destroy_tree(node *n)
{
	if (!n)
		return;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
	if ((**s) == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int expect(char **s, char c)
{
	if (accept(s, c))
		return (1);
	unexpected(**s);
	return (0);
}

// ...
node *get_num_node(char **s)
{
	node num;
	node *ret;

	if (isdigit(**s))
	{
		num.type = VAL;
		num.val = (**s) - '0';
		node *new_num = new_node(num);
		if (!new_num)
		{
			return NULL;
		}
		(*s)++;
		return (new_num);
	}
	else if ((**s) == '(')
	{
		(*s)++;
		ret = create_addition_tree(s);
		if (!ret || **s == '\0' || **s != ')')
		{
			destroy_tree(ret);
			return (NULL);
		}
		(*s)++;
		return (ret);
	}
	return NULL;
}

node *create_multi_tree(char **s)
{
	node multiply;
	node *left;
	node *right;

	left = get_num_node(s);
	if (!left)
		return NULL;
	while (**s == '*')
	{
		(*s)++;
		right = get_num_node(s);
		if (!right)
		{
			destroy_tree(left);
			return NULL;
		}
		multiply.type = MULTI;
		multiply.l = left;
		multiply.r = right;
		left = new_node(multiply);
		if (!left)
		{
			destroy_tree(right);
			return NULL;
		}
	}
	return (left);
}

node *create_addition_tree(char **s)
{
	node add;
	node *left;
	node *right;

	left = create_multi_tree(s);
	printf("Left %d\n", left->val);
	if (!left)
		return NULL;
	while (**s == '+')
	{
		(*s)++;
		right = create_multi_tree(s);
		printf("Right %d\n", right->val);
		if (!right)
		{
			destroy_tree(left);
			return NULL;
		}
		add.type = ADD;
		add.l = left;
		add.r = right;
		left = new_node(add);
		printf("Left %d\n", left->val);
		if (!left)
		{
			destroy_tree(right);
			return NULL;
		}
	}
	printf("Left %d\n", left->val);
	return (left);
}

node *parse_expr(char *s)
{
	//...
	node *ret;

	ret = create_addition_tree(&s);
	if (*s != '\0' || ret == NULL)
		unexpected(*s);

	if (*s)
	{
		destroy_tree(ret);
		return (NULL);
	}
	return (ret);
}

int eval_tree(node *tree)
{
	switch (tree->type)
	{
	case ADD:
		return (eval_tree(tree->l) + eval_tree(tree->r));
	case MULTI:
		return (eval_tree(tree->l) * eval_tree(tree->r));
	case VAL:
		return (tree->val);
	}
	return -1;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	node *tree = parse_expr(argv[1]);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
}