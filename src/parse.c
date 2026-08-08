#include "../include/cub3d.h"

static int read_scene(char *path, char **out)
{
	int fd = open(path, O_RDONLY);
	int n = 0;
	int got;
	char *buf = malloc(1024 * 1024);
	if (fd < 0 || !buf) { free(buf); if (fd >= 0) close(fd); return (0); }
	while ((got = read(fd, buf + n, 1024 * 1024 - n - 1)) > 0) n += got;
	close(fd);
	if (got < 0 || n == 1024 * 1024 - 1) { free(buf); return (0); }
	buf[n] = 0; *out = buf;
	return (1);
}

char *next_line(char **cursor)
{
	char *start = *cursor;
	char *line;
	int n = 0;
	int i;
	if (!*start) return (NULL);
	while (start[n] && start[n] != '\n') n++;
	if (n > 0 && start[n - 1] == '\r') n--;
	line = malloc(n + 1);
	if (!line) return (NULL);
	i = 0;
	while (i < n) { line[i] = start[i]; i++; }
	line[n] = 0;
	*cursor = start + n;
	if (**cursor == '\n') (*cursor)++;
	return (line);
}

static int texture_line(t_game *g, char *line, char *id, int slot)
{
	char *value;
	int n = str_len(id);
	if (line[0] != id[0] || line[1] != id[1]) return (0);
	if (!is_space(line[n])) return (-1);
	value = str_trim(line + n);
	if (!value || !value[0] || g->path[slot]) { free(value); return (-1); }
	g->path[slot] = value;
	return (1);
}

static int config_line(t_game *g, char *line, int *seen)
{
	int result;
	result = texture_line(g, line, "NO", 0); if (result) { if (result > 0) *seen |= 1; return (result > 0); }
	result = texture_line(g, line, "SO", 1); if (result) { if (result > 0) *seen |= 2; return (result > 0); }
	result = texture_line(g, line, "WE", 2); if (result) { if (result > 0) *seen |= 4; return (result > 0); }
	result = texture_line(g, line, "EA", 3); if (result) { if (result > 0) *seen |= 8; return (result > 0); }
	if ((line[0] == 'F' || line[0] == 'C') && is_space(line[1]))
	{
		if (line[0] == 'F' && (*seen & 16)) return (0);
		if (line[0] == 'C' && (*seen & 32)) return (0);
		if (!parse_color(line + 2, line[0] == 'F' ? &g->color_floor : &g->color_ceiling)) return (0);
		if (line[0] == 'F') (*seen) |= 16; else (*seen) |= 32;
		return (1);
	}
	return (0);
}

int parse_scene(t_game *g, char *path)
{
	char *file, *cursor, *line;
	int seen = 0;
	int map_started = 0;
	if (str_len(path) < 5 || !str_eq(path + str_len(path) - 4, ".cub") || !read_scene(path, &file)) return (0);
	cursor = file;
	while ((line = next_line(&cursor)))
	{
		char *trim = str_trim(line);
		if (!trim) { free(line); free(file); return (0); }
		if (!trim[0]) { free(trim); free(line); continue; }
		if (!map_started && (trim[0] == '0' || trim[0] == '1'))
		{
			if ((seen & 63) != 63) { free(trim); free(line); free(file); return (0); }
			map_started = 1; free(trim);
			seen = parse_map(g, cursor, line); free(line); free(file); return (seen);
		}
		if (map_started || !config_line(g, trim, &seen)) { free(trim); free(line); free(file); return (0); }
		free(trim); free(line);
	}
	free(file);
	return (map_started && (seen & 63) == 63 && parse_map(g, cursor, NULL));
}
