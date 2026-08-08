#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_W 1024
# define WIN_H 768
# define SPEED 0.075
# define ROT_SPEED 0.055

typedef struct s_tex
{
	void	*image;
	char	*data;
	int	width;
	int	height;
	int	bpp;
	int	line_len;
	int	endian;
}t_tex;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}t_player;

typedef struct s_game
{
	void	*mlx;
	void	*window;
	void	*image;
	char	*frame;
	int	bpp;
	int	line_len;
	int	endian;
	char	**map;
	int	map_w;
	int	map_h;
	char	*path[4];
	int	color_floor;
	int	color_ceiling;
	t_tex	textures[4];
	t_player	player;
	int	keys[6];
	int	closed;
}t_game;

int		parse_scene(t_game *game, char *path);
int		parse_map(t_game *game, char *cursor, char *first_line);
char	*next_line(char **cursor);
int		fatal(t_game *game, char *message);
void	free_game(t_game *game);
int		str_len(char *s);
int		str_eq(char *a, char *b);
int		is_space(char c);
char	*str_dup(char *s);
char	*str_trim(char *s);
int		parse_color(char *s, int *out);
int		load_textures(t_game *game);
void	start_game(t_game *game);
void	draw_frame(t_game *game);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
int		close_game(t_game *game);
int		game_loop(t_game *game);

#endif
