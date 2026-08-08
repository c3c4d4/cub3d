#include "../include/cub3d.h"

static int add_row(t_game *g, char *line, int count)
{
	char **rows = malloc(sizeof(char *) * (count + 2));
	int i;
	if (!rows) return (0);
	if (g->map) { i = 0; while (i < count) { rows[i] = g->map[i]; i++; } free(g->map); }
	rows[count] = str_dup(line);
	rows[count + 1] = NULL;
	if (!rows[count]) { free(rows); return (0); }
	g->map = rows;
	if (str_len(line) > g->map_w) g->map_w = str_len(line);
	return (1);
}

static int valid_cell(t_game *g, int x, int y)
{
	char c = g->map[y][x];
	if (c == '1' || c == ' ') return (1);
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W') return (0);
	if (x == 0 || y == 0 || x + 1 >= str_len(g->map[y]) || y + 1 >= g->map_h) return (0);
	if (g->map[y - 1][x] == ' ' || g->map[y + 1][x] == ' ' || g->map[y][x - 1] == ' ' || g->map[y][x + 1] == ' ') return (0);
	return (1);
}

static int player(t_game *g, int x, int y, char c)
{
	if (g->player.x) return (0);
	g->player.x = x + 0.5; g->player.y = y + 0.5;
	if (c == 'N') { g->player.dir_y = -1; g->player.plane_x = 0.66; }
	if (c == 'S') { g->player.dir_y = 1; g->player.plane_x = -0.66; }
	if (c == 'E') { g->player.dir_x = 1; g->player.plane_y = 0.66; }
	if (c == 'W') { g->player.dir_x = -1; g->player.plane_y = -0.66; }
	return (1);
}

int parse_map(t_game *g, char *cursor, char *first_line)
{
	char *line;
	int count = 0;
	int x, y;
	if (first_line && !add_row(g, first_line, count++)) return (0);
	while ((line = next_line(&cursor)))
	{
		if (!line[0] || !add_row(g, line, count++)) { free(line); return (0); }
		free(line);
	}
	g->map_h = count;
	if (!g->map) return (0);
	y = 0;
	while (y < g->map_h) { x = 0; while (x < str_len(g->map[y])) { if (!valid_cell(g, x, y)) return (0); if (g->map[y][x] != '0' && g->map[y][x] != '1' && g->map[y][x] != ' ') if (!player(g, x, y, g->map[y][x])) return (0); x++; } y++; }
	return (g->player.x != 0);
}
