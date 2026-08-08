#include "../include/cub3d.h"

int fatal(t_game *game, char *message)
{
	write(2, "Error\n", 6);
	write(2, message, str_len(message));
	write(2, "\n", 1);
	free_game(game);
	return (1);
}

void free_game(t_game *game)
{
	int i;
	if (!game) return ;
	i = 0;
	while (i < 4) { if (game->textures[i].image && game->mlx) mlx_destroy_image(game->mlx, game->textures[i].image); i++; }
	if (game->window && game->mlx) mlx_destroy_window(game->mlx, game->window);
	if (game->image && game->mlx) mlx_destroy_image(game->mlx, game->image);
	if (game->mlx) mlx_destroy_display(game->mlx);
	if (game->mlx) free(game->mlx);
	i = 0;
	while (i < 4) { free(game->path[i]); i++; }
	if (game->map) { i = 0; while (game->map[i]) free(game->map[i++]); free(game->map); }
}
