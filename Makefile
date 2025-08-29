NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit 
GLFW_PATH = $(shell brew --prefix glfw)/lib


SRCS = cub3D.c \
	   parssing/read_file.c			\
	   parssing/get_next_line.c		\
	   parssing/file_name.c			\
	   parssing/errors.c			\
	   parssing/leaks_mem.c			\
	   parssing/parssing_utils.c    \
	   parssing/texture_init.c		\
	   parssing/colors_init.c		\
	   parssing/parssing_map.c		\
	   parssing/check_wall.c		\
	   game_start/init_game.c		\
	   game_start/set_colors.c      \
	   game_start/draw.c     		\
	   game_start/handle_input.c    \


OBJS = $(SRCS:.c=.o)
LIB = libft/libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(LIB) $(OBJS)  $(MLXFLAGS) MlX42/build/libmlx42.a -Iinclude -lglfw -L$(GLFW_PATH) -o $(NAME)
%.o: %.c cub3D.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@make -C libft

clean:
	@rm -f $(OBJS)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

mlx:
	@git clone https://github.com/codam-coding-college/MLX42.git

build:
	@cmake MLX42 -B MLX42/build
	@make -C MLX42/build -j4
mlxclean:
	@rm -rf MLX42

re: fclean all
.PHONY: all clean fclean re
