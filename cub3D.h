/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:24:17 by ymouchta          #+#    #+#             */
/*   Updated: 2025/08/01 04:37:18 by yagame           ###   ########.fr       */
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

# define MALLOC "malloc faild"
# define CRCTR "caracter not valide"
# define WALL "wall not valide"
# define COLOR "colors not valide"
# define TEXT "textur not valide"
# define NAME "file name not valide"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif


typedef struct s_config
{
	char	*no_texture_path;
	char	*so_texture_path;
	char	*we_texture_path;
	char	*ea_texture_path;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_config;

typedef struct s_game
{
	mlx_t *mlx;
	t_config *conf;
	
} t_game;

// read
char	*get_next_line(int fd);
//errors
void	message_error(char *str);
// parssing
bool	parssing(t_config *game, char *f_name);
bool	check_name(char *name);
bool	path_name(char *name);
bool	color_init(t_config *game, char *str);
bool	parssing_map(t_config *game, char *str);

// parssing utils
int		size_tab(char **str);
char	*remove_nline(char *str);

// textur init
bool	text_init(t_config *game, char *line);
//leaks
void	clean_tab(char ***arg);
//check walls
bool	check_walls(int size, char **map);



// mlx helper function
int 		start_game(t_game *game);
uint32_t 	rgb_to_mlx_color(int r, int g, int b, int a);
void 		fill_rect(mlx_image_t *img, int x, int y, int width, int height, uint32_t color);
#endif