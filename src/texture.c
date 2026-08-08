#include "../include/cub3d.h"

int load_textures(t_game *g)
{
	int i;
	int *w;
	int *h;
	for (i = 0; i < 4; i++)
	{
		w = &g->textures[i].width; h = &g->textures[i].height;
		g->textures[i].image = mlx_xpm_file_to_image(g->mlx, g->path[i], w, h);
		if (!g->textures[i].image) return (0);
		g->textures[i].data = mlx_get_data_addr(g->textures[i].image, &g->textures[i].bpp, &g->textures[i].line_len, &g->textures[i].endian);
	}
	return (1);
}
