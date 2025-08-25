/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:24:17 by ymouchta          #+#    #+#             */
/*   Updated: 2025/08/25 18:05:12 by yagame           ###   ########.fr       */
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
#include "MLX42/include/MLX42/MLX42.h"

// colors
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
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
#define  TILE 32

typedef struct s_player{
	int x;
	int y;
	char dir;
	int speed;
	int angle;
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

// read
char	*get_next_line(int fd);
//errors
void	message_error(char *str);
// parssing
bool	parssing(t_game *game, char *f_name);
bool	check_name(char *name);
bool	path_name(char *name);
bool	color_init(t_game *game, char *str);
bool	parssing_map(t_game *game, char *str);

// parssing utils
int		size_tab(char **str);
char	*remove_nline(char *str);

// textur init
bool	text_init(t_game *game, char *line);
//leaks
void	clean_tab(char ***arg);
//check walls
bool	check_walls(int size, char **map);


// start game
int 		start_game(t_game *game);
void 		ft_set_ceil_floor_color(t_game * game);
void 		draw_map(t_game *g);
void 		_init(t_game *game);


#endif