#include "../include/cub3d.h"

static unsigned int pixel(char *data, int bpp, int line, int x, int y)
{
	unsigned int value = 0;
	int i;
	char *p = data + y * line + x * (bpp / 8);
	for (i = 0; i < bpp / 8; i++) value |= (unsigned char)p[i] << (i * 8);
	return (value);
}

static void put_pixel(t_game *g, int x, int y, unsigned int color)
{
	*(unsigned int *)(g->frame + y * g->line_len + x * (g->bpp / 8)) = color;
}

static int wall_texture(int side, double ray_x, double ray_y)
{
	if (side == 0) return (ray_x > 0 ? 3 : 2);
	return (ray_y > 0 ? 1 : 0);
}

static void ray_column(t_game *g, int x)
{
	double camera = 2.0 * x / WIN_W - 1.0;
	double ray_x = g->player.dir_x + g->player.plane_x * camera;
	double ray_y = g->player.dir_y + g->player.plane_y * camera;
	int map_x = (int)g->player.x, map_y = (int)g->player.y, side = 0;
	double delta_x = fabs(1 / ray_x), delta_y = fabs(1 / ray_y), step_x, step_y, side_x, side_y, distance;
	int line, start, end, y, tx, ty, texture;
	if (ray_x < 0) { step_x = -1; side_x = (g->player.x - map_x) * delta_x; } else { step_x = 1; side_x = (map_x + 1.0 - g->player.x) * delta_x; }
	if (ray_y < 0) { step_y = -1; side_y = (g->player.y - map_y) * delta_y; } else { step_y = 1; side_y = (map_y + 1.0 - g->player.y) * delta_y; }
	while (g->map[map_y][map_x] != '1') { if (side_x < side_y) { side_x += delta_x; map_x += step_x; side = 0; } else { side_y += delta_y; map_y += step_y; side = 1; } }
	distance = side ? side_y - delta_y : side_x - delta_x; line = (int)(WIN_H / distance); start = -line / 2 + WIN_H / 2; end = line / 2 + WIN_H / 2;
	if (start < 0) start = 0;
	if (end >= WIN_H) end = WIN_H - 1;
	for (y = 0; y < start; y++) put_pixel(g, x, y, g->color_ceiling);
	texture = wall_texture(side, ray_x, ray_y);
	for (; y <= end; y++) { double hit = side ? g->player.x + distance * ray_x : g->player.y + distance * ray_y; hit -= floor(hit); tx = (int)(hit * g->textures[texture].width); if (tx >= g->textures[texture].width) tx = g->textures[texture].width - 1; ty = ((y - start) * g->textures[texture].height) / (end - start + 1); put_pixel(g, x, y, pixel(g->textures[texture].data, g->textures[texture].bpp, g->textures[texture].line_len, tx, ty)); }
	for (; y < WIN_H; y++) put_pixel(g, x, y, g->color_floor);
}

void draw_frame(t_game *g)
{
	int x;
	g->frame = mlx_get_data_addr(g->image, &g->bpp, &g->line_len, &g->endian);
	for (x = 0; x < WIN_W; x++) ray_column(g, x);
	mlx_put_image_to_window(g->mlx, g->window, g->image, 0, 0);
}
