#include "vbc.h"

void free_list(node *list)
{
	node *tmp;

	while (list)
	{
		tmp = list;
		list = list->r;
		free(tmp);
	}
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

void add_node(node **list, char t, int n)
{
	node *new = calloc(1, sizeof(node));
	if (!new)
		return ;

	new->type = t;
	if (t == 'n')
		new->val = n;
	else
		new->val = -101;
	new->r = NULL;
	new->l = NULL;
	if (!*list)
	{
		*list = new;
		(*list)->tail = new;
		return ;
	}
	(*list)->tail->r = new;
	new->l = (*list)->tail;
	(*list)->tail = new;
}

void wrap_exit(char c, node **list)
{
	unexpected(c);
	free_list(*list);
	*list = NULL;
}

int error_parse(char t, char c)
{
	if (t == 'n')
	{
		if (!(c == '(' || c == ')' || c == '+' || c == '*'))
			return (1);
	}
	if (t == '(')
	{
		if (c == ')' || c == '+' || c == '*')
			return (1);
	}
	if (t == ')')
	{
		if (c == '(')
			return (1);
	}
	if (t == '+' || t == '*')
	{
		if (c == '+' || c == '*' || c == ')')
			return (1);
	}
	return (0);
}

node *parse_expr(char *s)
{
	node *list = NULL;
	int val;
	int type;
	int par_ouv = 0;
	int par_fer = 0;

	while (*s)
	{
		if (isdigit(*s))
		{
			val = *s - '0';
			type = 'n';
			s++;
		}
		else if (*s == '(')
		{
			par_ouv++;
			val = -101;
			type = *s;
			s++;
		}
		else if (*s == ')')
		{
			par_fer++;
			val = -101;
			type = *s;
			s++;
		}
		else if (*s == '*' || *s == '+')
		{
			val = -101;
			type = *s;
			s++;
		}
		else
		{
			wrap_exit(*s, &list);
			return (NULL);
		}
		if (error_parse(type, *s))
		{
			wrap_exit(*s, &list);
			return (NULL);
		}
		add_node(&list, type, val);
	}
	if (par_ouv > par_fer)
		wrap_exit('(', &list);
	else if (par_ouv < par_fer)
		wrap_exit(')', &list);
	
	return (list);
}