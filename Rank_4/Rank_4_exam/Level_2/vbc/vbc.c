#include <stdio.h>
#include <stdlib.h> // change malloc.h to stdlib.h
#include <ctype.h>

typedef struct node {
    enum { ADD, MULTI, VAL } type;
    int val;
    struct node *l, *r;
} node;

node *new_node(node n) {
    node *ret = calloc(1, sizeof(n));      // sizeof(n)
    if (!ret) exit(1); // add a exit 
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
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

void unexpected(char c) {
    if (c) printf("Unexpected token '%c'\n", c);
    else printf("Unexpected end of input\n"); // change "file" to "input"
    exit(1); // add exit
}

int accept(char **s, char c) {
    if (**s == c) { // add a 'c' check
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c) {
    if (accept(s, c)) return (1);
    unexpected(**s);
    return (0);
}

// --- MiNiMaL PARSING BlOcK ---===================================================
node *expr(char **s);

node *factor(char **s) {
    if (isdigit(**s)) {
        int v = *(*s)++ - '0';
        return new_node((node){VAL, v, 0, 0});
    }
    expect(s, '(');
    node *res = expr(s);
    expect(s, ')');
    return res;
}

node *term(char **s) {
    node *l = factor(s);
    while (accept(s, '*'))
        l = new_node((node){MULTI, 0, l, factor(s)});
    return l;
}

node *expr(char **s) {
    node *l = term(s);
    while (accept(s, '+'))
        l = new_node((node){ADD, 0, l, term(s)});
    return l;
}
// ----------------------------===================================================

node *parse_expr(char *s) {
    node *res = expr(&s);
    if (*s) unexpected(*s); 
    return res;
}

int eval_tree(node *t) {
    if (t->type == VAL) return t->val;
    if (t->type == ADD) return eval_tree(t->l) + eval_tree(t->r);
    return eval_tree(t->l) * eval_tree(t->r);
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    node *tree = parse_expr(argv[1]);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
    return 0;                             // ADD a ret 0
}