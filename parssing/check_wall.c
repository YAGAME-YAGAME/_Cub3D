/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:00:00 by yagame            #+#    #+#             */
/*   Updated: 2025/08/27 18:26:39 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	check_adjacent_cells(t_game *game, int x, int y)
{
	char	**map;
	int		height;
	int		width;

	map = game->conf->map;
	height = game->conf->map_height;
	width = game->conf->map_width;
	
	// Check all 4 cardinal directions (not diagonals for this check)
	// Up
	if (y > 0)
	{
		if (map[y-1][x] == ' ')
			return (0);
	}
	else
		return (0); // Can't be at top border
	
	// Down
	if (y < height - 1)
	{
		if (map[y+1][x] == ' ')
			return (0);
	}
	else
		return (0); // Can't be at bottom border
		
	// Left
	if (x > 0)
	{
		if (map[y][x-1] == ' ')
			return (0);
	}
	else
		return (0); // Can't be at left border
		
	// Right
	if (x < width - 1)
	{
		if (map[y][x+1] == ' ')
			return (0);
	}
	else
		return (0); // Can't be at right border
	
	return (1);
}

int	find_player(t_game *game)
{
	int		x, y;
	int		player_count;
	char	**map;

	map = game->conf->map;
	player_count = 0;
	y = 0;
	while (y < game->conf->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(map[y]))
		{
			if (is_player_char(map[y][x]))
			{
				game->player.x = x * TILE + TILE / 2;
				game->player.y = y * TILE + TILE / 2;
				game->player.dir = map[y][x];
				player_count++;
				// Replace player position with '0' in the map
				map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (player_count == 1);
}

int	check_map_walls(t_game *game)
{
	int		x, y;
	char	**map;

	map = game->conf->map;
	
	// Check that walkable areas are properly enclosed
	for (y = 0; y < game->conf->map_height; y++)
	{
		for (x = 0; x < game->conf->map_width; x++)
		{
			// Only check walkable areas (0) and player positions
			if (map[y][x] == '0' || is_player_char(map[y][x]))
			{
				// Check if this walkable area is properly enclosed
				if (!check_adjacent_cells(game, x, y))
				{
					printf("Map not enclosed at position (%d, %d) - char: '%c'\n", x, y, map[y][x]);
					return (0);
				}
			}
		}
	}
	return (1);
}
