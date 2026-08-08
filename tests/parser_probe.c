#include "../include/cub3d.h"

void free_game(t_game *game)
{
	int i = 0;
	while (i < 4) free(game->path[i++]);
	if (game->map) { i = 0; while (game->map[i]) free(game->map[i++]); free(game->map); }
}

int main(void)
{
	t_game game;
	int i = 0;
	while (i < (int)sizeof(game)) ((char *)&game)[i++] = 0;
	if (!parse_scene(&game, "scenes/demo.cub")) { printf("valid scene rejected\n"); return (1); }
	free_game(&game);
	i = 0;
	while (i < (int)sizeof(game)) ((char *)&game)[i++] = 0;
	if (parse_scene(&game, "tests/invalid.cub")) { printf("invalid scene accepted\n"); return (2); }
	free_game(&game);
	return (0);
}
