#include "argo.h"
// #define DEBUG

int		peek(FILE *stream);
void	unexpected(FILE *stream);
int		accept(FILE *stream, char c);
int		expect(FILE *stream, char c);
int		argo(json *dst, FILE *stream);
json	parse_json(FILE *stream);
json	parse_string_json(FILE *stream);
json	parse_map(FILE *stream);
json	parse_number(FILE *stream);
char	*parse_string(FILE *stream);
void	debug_print_cur_char(FILE *stream, char const *msg);
void	set_g_error(void);

static int		g_error = 0;
static int		g_error_no_key = 0;

int	argo(json *dst, FILE *stream)
{
	if (!stream)
		return (-1);

	*dst = parse_json(stream);
	if (g_error_no_key)
	{
		return (-1);
	}
	if (g_error)
	{
		unexpected(stream);
		return (-1);
	}
	return (1);
}

json	parse_json(FILE *stream)
{
	json	nothing;

	if (peek(stream) == '"')
		return (parse_string_json(stream));
	if (peek(stream) == '{')
		return (parse_map(stream));
	if (peek(stream) == '-' || isdigit(peek(stream)))
		return (parse_number(stream));
	nothing.type = STRING;
	nothing.string = NULL;
	g_error = 1;
	return (nothing);
}

json	parse_map(FILE *stream)
{
	json	json_map = {.type = MAP, .map = {.data =NULL, .size = 0}};
	//Skip opening curly brace
	if (!accept(stream, '{'))
	{
		g_error = 1;
		return (json_map);
	}
	do
	{
		pair new_pair;
		new_pair.key = parse_string(stream);
		if (g_error)
		{
			g_error_no_key = 1;
			free(new_pair.key);
			return (json_map);
		}
		if (!accept(stream, ':'))
		{
			g_error = 1;
			return (json_map);
		}
		new_pair.value = parse_json(stream);
		if (g_error)
		{
			free(new_pair.key);
			free_json(new_pair.value);
			return (json_map);
		}
		json_map.map.size++;
		json_map.map.data = realloc(json_map.map.data, json_map.map.size
				* sizeof(pair));
		json_map.map.data[json_map.map.size - 1] = new_pair;
	} while (accept(stream, ','));
	if (!accept(stream, '}'))
	{
		g_error = 1;
		return (json_map);
	}
	return (json_map);
}

json	parse_string_json(FILE *stream)
{
	json	json_string;

	json_string.type = STRING;
	json_string.string = parse_string(stream);
	return (json_string);
}

char	*parse_string(FILE *stream)
{
	char	*res;
	char	cur_char;
	int		str_len;

	res = malloc(sizeof(char));
	res[0] = '\0';
	str_len = 0;
	//Skip first quote
	if (!accept(stream, '"'))
	{
		g_error = 1;
		return (res);
	}
	while (peek(stream) != '"' && peek(stream) != EOF && !g_error)
	{
		#ifdef DEBUG
			debug_print_cur_char(stream, "PARSING STRING ");
		#endif
		str_len++;
		res = realloc(res, (str_len + 1) * sizeof(char));
		res[str_len] = '\0';
		cur_char = getc(stream); // Read one char from stream
		if (cur_char == '\\') // If it's a backslash, check for escape sequence
		{
			if (peek(stream) != '\\' && peek(stream) != '\"') // Ensure valid escape
			{
				g_error = 1;
				return (res); // Return early if its; an invalid escape sequence
			}
			cur_char = getc(stream); // Read and consume the next char (escaped one)
		}
		res[str_len - 1] = cur_char; // Store the processed char in the buffer
	}
	// Skip last quote
	if (!accept(stream, '"'))
	{
		g_error = 1;
	}
	return (res);
}

json	parse_number(FILE *stream)
{
	json	num_json;
	int		res;
	int		ret_fscanf;

	num_json.type = INTEGER;
	num_json.integer = -42; // sentinel value
	ret_fscanf = fscanf(stream, "%d", &res);
	if (ret_fscanf <= 0 || ret_fscanf == EOF)
	{
		g_error = 1;;
		return (num_json);
	}
	num_json.integer = res;
	return (num_json);
}

void	debug_print_cur_char(FILE *stream, char const *msg)
{
	if (msg)
	{
		printf("%s", msg);
	}
	printf("CUR_CHAR: %c\n", peek(stream));
}
