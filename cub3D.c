/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:49:15 by ymouchta          #+#    #+#             */
/*   Updated: 2025/08/01 04:15:10 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "MLX42/include/MLX42/MLX42.h"



void	desplay_struct(t_config *game)
{
	int	i;

	printf("NO Texture Path: %s\n", game->no_texture_path);
	printf("SO Texture Path: %s\n", game->so_texture_path);
	printf("WE Texture Path: %s\n", game->we_texture_path);
	printf("EA Texture Path: %s\n", game->ea_texture_path);
	printf("Floor Color: %d\n", game->floor_color);
	printf("Ceiling Color: %d\n", game->ceiling_color);
	printf("Player Position: (%d, %d)\n", game->player_x, game->player_y);
	printf("Player Direction: %c\n", game->player_dir);
	printf("Map Width: %d\n", game->map_width);
	printf("Map Height: %d\n", game->map_height);
	i = 0;
	if (game->map)
	{
		printf("Map:\n");
		while (game->map[i])
		{
			printf("%s\n", game->map[i]);
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_game	game;
	
	game.conf = malloc(sizeof(game.conf));
	if (!game.conf)
		return (message_error("error malloc"), 1);
	if (ac != 2)
		message_error("error in argument");
	if (!parssing(game.conf, av[1]))
		{return (1);}
	if(start_game(&game))
		return (EXIT_FAILURE);
}
