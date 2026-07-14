#ifndef VBC_H
# define VBC_H

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct node {
    char type;
    int val;
	struct node *tail;
    struct node *l;
    struct node *r;
}   node;

void    unexpected(char c);
node *parse_expr(char *s);
void free_list(node *list);

#endif