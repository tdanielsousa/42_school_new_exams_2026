#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

typedef struct node {
	enum {
		ADD,
		MULTI,
		VAL
	}	type;
	int				val;
	struct node		*l;
	struct node		*r;
}	node;

/* Изменено: использование sizeof(*ret) для корректного выделения памяти */
node	*new_node(node n)
{
	node	*ret;

	ret = calloc(1, sizeof(*ret));
	if (!ret)
		exit(1);
	*ret = n;
	return (ret);
}

void	destroy_tree(node *n)
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

/* Изменено: сообщение об ошибке приведено в соответствие с subject */
void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

/* Изменено: добавлена проверка символа перед инкрементом указателя */
int	accept(char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int	expect(char **s, char c)
{
	if (accept(s, c))
		return (1);
	unexpected(**s);
	return (0);
}
////////////////////////////////////////////////////////////////////////
/* Добавлено: рекурсивный спуск для обработки приоритетов операций */
static node	*parse_expr_r(char **s);

static node	*parse_factor(char **s)
{
	node	*e;
	node	n;

	if (isdigit((unsigned char)**s))
	{
		n.type = VAL;
		n.val = **s - '0';
		n.l = NULL;
		n.r = NULL;
		(*s)++;
		return (new_node(n));
	}
	if (accept(s, '('))
	{
		e = parse_expr_r(s);
		if (!e)
			return (NULL);
		if (!expect(s, ')'))
		{
			destroy_tree(e);
			exit(1);
		}
		return (e);
	}
	unexpected(**s);
	exit(1);
}

/* Добавлено: функция для обработки умножения (высокий приоритет) */
static node	*parse_term(char **s)
{
	node	*left;
	node	*right;
	node	n;

	left = parse_factor(s);
	while (accept(s, '*'))
	{
		right = parse_factor(s);
		n.type = MULTI;
		n.l = left;
		n.r = right;
		left = new_node(n);
	}
	return (left);
}

/* Добавлено: функция для обработки сложения (низкий приоритет) */
static node	*parse_expr_r(char **s)
{
	node	*left;
	node	*right;
	node	n;

	left = parse_term(s);
	while (accept(s, '+'))
	{
		right = parse_term(s);
		n.type = ADD;
		n.l = left;
		n.r = right;
		left = new_node(n);
	}
	return (left);
}

/* Изменено: проверка остатка строки после парсинга */
node	*parse_expr(char *s)
{
	char	*p;
	node	*ret;

	p = s;
	ret = parse_expr_r(&p);
	if (*p)
	{
		unexpected(*p);
		destroy_tree(ret);
		exit(1);
	}
	return (ret);
}
////////////////////////////////////////////////////////////////////////
int	eval_tree(node *tree)
{
	if (tree->type == ADD)
		return (eval_tree(tree->l) + eval_tree(tree->r));
	if (tree->type == MULTI)
		return (eval_tree(tree->l) * eval_tree(tree->r));
	return (tree->val);
}

int	main(int argc, char **argv)
{
	node	*tree;

	if (argc != 2)
		return (1);
	tree = parse_expr(argv[1]);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0);
}