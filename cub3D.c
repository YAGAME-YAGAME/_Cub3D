/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:49:15 by ymouchta          #+#    #+#             */
/*   Updated: 2025/08/25 18:21:34 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "MLX42/include/MLX42/MLX42.h"



void	desplay_struct(t_game *game)
{
	int	i;

	printf("NO Texture Path: %s\n", game->conf->no_texture_path);
	printf("SO Texture Path: %s\n", game->conf->so_texture_path);
	printf("WE Texture Path: %s\n", game->conf->we_texture_path);
	printf("EA Texture Path: %s\n", game->conf->ea_texture_path);
	printf("Floor Color: %d\n", game->conf->floor_color);
	printf("Ceiling Color: %d\n", game->conf->ceiling_color);
	printf("Player Position: (%d, %d)\n", game->player.x, game->player.y);
	printf("Player Direction: %c\n", game->player.dir);
	printf("Map Width: %d\n", game->conf->map_width);
	printf("Map Height: %d\n", game->conf->map_height);
	i = 0;
	if (game->conf->map)
	{
		printf("Map:\n");
		while (game->conf->map[i])
		{
			printf("%s\n", game->conf->map[i]);
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
	_init(&game);
	if (!parssing(&game, av[1]))
		{return (1);}
	// desplay_struct(&game);
	if(start_game(&game))
		return (EXIT_FAILURE);
	return (0);
}
