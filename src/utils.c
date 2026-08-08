#include "../include/cub3d.h"

int str_len(char *s)
{
	int i = 0;
	while (s && s[i]) i++;
	return (i);
}

int str_eq(char *a, char *b)
{
	int i = 0;
	if (!a || !b) return (0);
	while (a[i] && b[i] && a[i] == b[i]) i++;
	return (a[i] == b[i]);
}

int is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r');
}

char *str_dup(char *s)
{
	char *copy;
	int i;
	if (!s) return (NULL);
	copy = malloc(str_len(s) + 1);
	if (!copy) return (NULL);
	i = 0;
	while (s[i]) { copy[i] = s[i]; i++; }
	copy[i] = 0;
	return (copy);
}

char *str_trim(char *s)
{
	int start = 0;
	int end = str_len(s);
	int length;
	char *out;
	while (is_space(s[start])) start++;
	while (end > start && is_space(s[end - 1])) end--;
	length = end - start;
	out = malloc(length + 1);
	if (!out) return (NULL);
	while (start < end) { out[start - (end - length)] = s[start]; start++; }
	out[length] = 0;
	return (out);
}
