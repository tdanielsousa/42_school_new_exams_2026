#include "argo.h"
#include <stdlib.h>
#include <ctype.h>

static int parse_value(json *j, FILE *s);
static int parse_string(json *j, FILE *s);
static int parse_int(json *j, FILE *s);
static int parse_map(json *j, FILE *s);

int argo(json *j, FILE *s)
{
	if (parse_value(j, s) != 1)
		return -1;
	if (peek(s) != EOF)
	{
		unexpected(s);
		return -1;
	}
	return 1;
}

static int parse_value(json *j, FILE *s)
{
	int c = peek(s);

	if (c == '"')
		return parse_string(j, s);
	if (c == '{')
		return parse_map(j, s);
	if (c == '-' || isdigit(c))
		return parse_int(j, s);
	unexpected(s);
	return -1;
}

static int parse_string(json *j, FILE *s)
{
	if (!accept(s, '"'))
	{
		unexpected(s);
		return -1;
	}

	char *buf = NULL;
	size_t len = 0, cap = 0;

	while (1)
	{
		int c = getc(s);
		if (c == EOF)
		{
			free(buf);
			unexpected(s);
			return -1;
		}
		if (c == '"')
			break;
		if (c == '\\')
		{
			int n = getc(s);
			if (n != '\\' && n != '"')
			{
				ungetc(n, s);
				free(buf);
				unexpected(s);
				return -1;
			}
			c = n;
		}
		if (len + 1 >= cap)
		{
			cap = cap ? cap * 2 : 16;
			buf = realloc(buf, cap);
			if (!buf)
				return -1;
		}
		buf[len++] = c;
	}
	if (len + 1 >= cap)
	{
		cap = cap ? cap + 1 : 1;
		buf = realloc(buf, cap);
	}
	buf[len] = 0;

	j->type = STRING;
	j->string = buf;
	return 1;
}

static int parse_int(json *j, FILE *s)
{
	long val = 0;
	int neg = 0;

	if (accept(s, '-'))
		neg = 1;

	if (!isdigit(peek(s)))
	{
		unexpected(s);
		return -1;
	}
	while (isdigit(peek(s)))
		val = val * 10 + (getc(s) - '0');

	j->type = INTEGER;
	j->integer = neg ? -val : val;
	return 1;
}

static int parse_map(json *j, FILE *s)
{
	if (!accept(s, '{'))
	{
		unexpected(s);
		return -1;
	}

	j->type = MAP;
	j->map.data = NULL;
	j->map.size = 0;

	if (accept(s, '}'))
		return 1;

	while (1)
	{
		json key, val;

		if (parse_string(&key, s) != 1)
			return -1;

		if (!accept(s, ':'))
		{
			free(key.string);
			unexpected(s);
			return -1;
		}

		if (parse_value(&val, s) != 1)
		{
			free(key.string);
			return -1;
		}

		pair *new = realloc(j->map.data, sizeof(pair) * (j->map.size + 1));
		if (!new)
		{
			free(key.string);
			free_json(val);
			return -1;
		}

		j->map.data = new;
		j->map.data[j->map.size].key = key.string;
		j->map.data[j->map.size].value = val;
        j->map.size++;

		if (accept(s, '}'))
			break;
		if (!accept(s, ','))
		{
			unexpected(s);
			return -1;
		}
	}
	return 1;
}
