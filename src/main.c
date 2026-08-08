#include "../include/cub3d.h"

void start_game(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx || !load_textures(g)) { fatal(g, "failed to initialize MiniLibX or load a texture"); exit(1); }
	g->window = mlx_new_window(g->mlx, WIN_W, WIN_H, "cub3D");
	g->image = mlx_new_image(g->mlx, WIN_W, WIN_H);
	if (!g->window || !g->image) { fatal(g, "failed to create the window"); exit(1); }
	mlx_hook(g->window, 2, 1L << 0, (int (*)())key_press, g);
	mlx_hook(g->window, 3, 1L << 1, (int (*)())key_release, g);
	mlx_hook(g->window, 17, 0, (int (*)())close_game, g);
	mlx_loop_hook(g->mlx, (int (*)())game_loop, g);
	mlx_loop(g->mlx);
}

int main(int argc, char **argv)
{
	t_game game;
	int i;
	(void)i;
	for (i = 0; i < (int)sizeof(game); i++) ((char *)&game)[i] = 0;
	if (argc != 2) return (fatal(&game, "usage: ./cub3D scene.cub"));
	if (!parse_scene(&game, argv[1])) return (fatal(&game, "invalid scene description"));
	start_game(&game);
	return (0);
}
