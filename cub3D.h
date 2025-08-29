/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:24:17 by ymouchta          #+#    #+#             */
/*   Updated: 2025/08/27 18:26:53 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"

// colors
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define PURPLE  "\x1b[35m"
# define CYAN    "\x1b[36m"
# define WHITE   "\x1b[37m"
# define RESET   "\x1b[0m"

# define MALLOC "malloc faild"
# define CRCTR "caracter not valide"
# define WALL "wall not valide"
# define COLOR "colors not valide"
# define TEXT "textur not valide"
# define NAME "file name not valide"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

#define WIDTH 1024
#define HEIGHT 750
#define  TILE 20

typedef struct s_player{
	int x;
	int y;
	char dir;
	int speed;
	float angle;
} t_player;

typedef struct s_config
{
	char	*no_texture_path;
	char	*so_texture_path;
	char	*we_texture_path;
	char	*ea_texture_path;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	mlx_image_t *img;
	int		map_width;
	int		map_height;
	// int		player_x;
	// int		player_y;
	// char	player_dir;
}	t_config;

typedef struct s_game
{
	mlx_t *mlx;
	t_config *conf;
	t_player player;
	
} t_game;

// parsing functions
int			parssing_map(t_game *game, char *file_name);
void		message_error(char *msg);
char		*get_next_line(int fd);
int			check_file_name(char *file_name);
void		free_split(char **split);
void		free_game(t_game *game);
int			parse_texture(t_game *game, char *line);
int			parse_color(t_game *game, char *line);
int			parse_map_lines(t_game *game, char **lines, int start_index);
int			check_map_walls(t_game *game);
int			find_player(t_game *game);
char		**read_file_lines(char *filename, int *line_count);
int			is_valid_map_char(char c);
int			is_player_char(char c);
char		*trim_whitespace(char *str);
int			count_lines_in_file(char *filename);

// start game
int 		start_game(t_game *game);
void 		ft_set_ceil_floor_color(t_game * game);
void 		draw_minimap(t_game *g);
void 		_init(t_game *game);
void 		handle_input(void *param);

#endif