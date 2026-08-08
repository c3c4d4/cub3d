#include "../include/cub3d.h"

static int number(char **s, int *value)
{
	int n = 0;
	while (is_space(**s)) (*s)++;
	if (**s < '0' || **s > '9') return (0);
	while (**s >= '0' && **s <= '9') { n = n * 10 + *(*s)++ - '0'; if (n > 255) return (0); }
	*value = n;
	return (1);
}

int parse_color(char *s, int *out)
{
	int r, g, b;
	if (!number(&s, &r) || *s++ != ',' || !number(&s, &g) || *s++ != ',' || !number(&s, &b)) return (0);
	while (is_space(*s)) s++;
	if (*s) return (0);
	*out = (r << 16) | (g << 8) | b;
	return (1);
}
