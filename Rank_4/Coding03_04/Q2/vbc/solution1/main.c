#include "vbc.h"

/*
Ce problème est similaire au leetcode224.
-----------------------------------------

Chaque caractere de argv[1] est contenue dans un élément d'une liste doublement chainée.

La fonction op_plus_etoile calcule une expression jusqu'à la fin de la string ou ')' en faisant deux passages.
Le premier calcule les multiplications; quand '*' est trouvé, le resultat entre le nombre a gauche et le nombre a droite est stocké dans l'element de gauche.
Le signe et l'élément de droite sont supprimés de la liste. La liste est rechainée.
Le deuxième passage calcule les '+'.

parenthesis calcule les parentheses;
En parcourant la liste de gauche à droite, on trouve le premier ')'. Puis on parcourt de droite à gauche pour trouver '('.
On recupère le resultat de l'expression entre ces parenthèses avec op_plus_etoile. Le resultat est stocké dans l'élément à droite de '('.
L'élément '(' et l'élément à la droite de sa droite sont supprimés.

On revient au début. rebolote, jusqu'à ce qu'il ne reste plus de parentheses. op_plus_etoile calcule le resultat final
---------------------------------------------

La logique de ce code est simple(?) mais longue. Il consomme beaucoup de ressources et de temps et il risque de timeout à l'examen lol !
Mais il a été accepté au leetcode

*/

void print_list(node *list)
{
	while (list)
	{
		if (list->type == 'n')
			printf("%d ", list->val);
		else
			printf("%c ", list->type);
		list = list->r;
	}
	printf("\n");
}

void delete_node(node **list, node *to_del)
{
	if (!*list || !to_del)
		return ;

	node *prev = to_del->l;
	node *next = to_del->r;

	if (prev)
		prev->r = next;
	else
		*list = next;
	if (next)
		next->l = prev;
	
	free(to_del);
}

void op_plus_etoile(node **list)//calcul pour une expression sans parenthese
{
	node *scan = *list;
	node *reset = NULL;
	node *next = NULL;

	while (scan && scan->type != ')')
	{
		if (scan->type == '*')
		{
			int res = scan->l->val * scan->r->val;
			reset = scan->l;
			reset->val = res;
			reset->type = 'n';
			next = scan->r->r;//peut etre NULL

			delete_node(list, scan->r);
			delete_node(list, scan);
			scan = next;
		}
		else
			scan = scan->r;
	}
	scan = *list;
	while (scan && scan->type != ')')
	{
		if (scan->type == '+')
		{
			int res = scan->l->val + scan->r->val;
			reset = scan->l;
			reset->val = res;
			reset->type = 'n';
			next = scan->r->r;

			delete_node(list, scan->r);
			delete_node(list, scan);
			scan = next;
		}
		else
			scan = scan->r;
	}
}

void parenthesis(node **list)
{
	node *scan = *list;

	while (scan)
	{
		if (scan->type == ')')
		{
			while (scan && scan->type != '(')
				scan = scan->l;
			op_plus_etoile(&(scan->r));
			delete_node(list, scan->r->r);
			delete_node(list, scan);
			scan = *list;
		}
		else
			scan = scan->r;
	}
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    node *list = parse_expr(argv[1]);
    if (!list)
        return (1);
    
	parenthesis(&list);
	op_plus_etoile(&list);
	print_list(list);
    free_list(list);
	return (0);
}