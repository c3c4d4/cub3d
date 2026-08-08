#include "../include/cub3d.h"

static void rotate(t_game *g, double angle)
{
	double old_x = g->player.dir_x;
	double old_plane = g->player.plane_x;
	g->player.dir_x = g->player.dir_x * cos(angle) - g->player.dir_y * sin(angle);
	g->player.dir_y = old_x * sin(angle) + g->player.dir_y * cos(angle);
	g->player.plane_x = g->player.plane_x * cos(angle) - g->player.plane_y * sin(angle);
	g->player.plane_y = old_plane * sin(angle) + g->player.plane_y * cos(angle);
}

static int open_cell(t_game *g, double x, double y)
{
	int ix = (int)x, iy = (int)y;
	return (iy >= 0 && iy < g->map_h && ix >= 0 && ix < str_len(g->map[iy]) && g->map[iy][ix] != '1' && g->map[iy][ix] != ' ');
}

static void move_player(t_game *g, double dx, double dy)
{
	if (open_cell(g, g->player.x + dx, g->player.y)) g->player.x += dx;
	if (open_cell(g, g->player.x, g->player.y + dy)) g->player.y += dy;
}

int key_press(int key, t_game *g)
{
	if (key == 65307) return (close_game(g));
	if (key == 119) g->keys[0] = 1;
	if (key == 115) g->keys[1] = 1;
	if (key == 97) g->keys[2] = 1;
	if (key == 100) g->keys[3] = 1;
	if (key == 65361) g->keys[4] = 1;
	if (key == 65363) g->keys[5] = 1;
	return (0);
}

int key_release(int key, t_game *g)
{
	if (key == 119) g->keys[0] = 0;
	if (key == 115) g->keys[1] = 0;
	if (key == 97) g->keys[2] = 0;
	if (key == 100) g->keys[3] = 0;
	if (key == 65361) g->keys[4] = 0;
	if (key == 65363) g->keys[5] = 0;
	return (0);
}

int close_game(t_game *g)
{
	if (!g->closed) { g->closed = 1; free_game(g); }
	exit(0);
}

int game_loop(t_game *g)
{
	double dx = 0, dy = 0;
	if (g->keys[0]) { dx += g->player.dir_x * SPEED; dy += g->player.dir_y * SPEED; }
	if (g->keys[1]) { dx -= g->player.dir_x * SPEED; dy -= g->player.dir_y * SPEED; }
	if (g->keys[2]) { dx += g->player.dir_y * SPEED; dy -= g->player.dir_x * SPEED; }
	if (g->keys[3]) { dx -= g->player.dir_y * SPEED; dy += g->player.dir_x * SPEED; }
	move_player(g, dx, dy); if (g->keys[4]) rotate(g, -ROT_SPEED); if (g->keys[5]) rotate(g, ROT_SPEED); draw_frame(g); return (0);
}
