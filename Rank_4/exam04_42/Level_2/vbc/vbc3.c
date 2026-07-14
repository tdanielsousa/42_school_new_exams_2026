#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int parse_expr(char **s);
int parse_term(char **s);
int parse_factor(char **s);

void error(char c) {
    printf("Unexpected token '%c'\n", c ? c : '0');
    exit(1);
}

int parse_factor(char **s) {
    if (isdigit(**s))
        return (*(*s)++ - '0');
    
    if (**s == '(') {
        (*s)++;
        int val = parse_expr(s);
        if (*(*s)++ != ')')
            error(*((*s) - 1));
        return val;
    }
    error(**s);
    return 0;
}

int parse_term(char **s) {
    int left = parse_factor(s);
    while (**s == '*') {
        (*s)++;
        left *= parse_factor(s);
    }
    return left;
}

int parse_expr(char **s) {
    int left = parse_term(s);
    while (**s == '+') {
        (*s)++;
        left += parse_term(s);
    }
    return left;
}

int main(int argc, char **argv) {
    if (argc != 2)
        return 1;
    
    char *s = argv[1];
    int result = parse_expr(&s);
    
    if (*s)
        error(*s);
    
    printf("%d\n", result);
    return 0;
}