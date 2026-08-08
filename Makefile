NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wno-cast-function-type
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
INCLUDES = -Iinclude -I$(MLX_DIR)
SRC = src/main.c src/utils.c src/error.c src/parse.c src/color.c src/map.c \
	src/texture.c src/render.c src/input.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -lXext -lX11 -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

parser-test:
	$(CC) $(CFLAGS) $(INCLUDES) tests/parser_probe.c src/utils.c src/color.c src/parse.c src/map.c -o tests/parser_probe
	./tests/parser_probe
	-rm -f tests/parser_probe

.PHONY: all clean fclean re bonus parser-test
