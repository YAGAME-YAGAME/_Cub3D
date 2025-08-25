/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:39:57 by ymouchta          #+#    #+#             */
/*   Updated: 2025/08/25 17:06:36 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	valid_cara(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (2);
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	else
		return (0);
}

int	find_player(t_game *game, int x, int y, char c)
{
	game->player.x = x;
	game->player.y = y;
	game->player.dir = c;
	return (1);
}

bool	check_caracter(t_game *game, char **map)
{
	int	i;
	int	j;
	int	check;

	i = -1;
	check = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (valid_cara(map[i][j]))
			{
				if (valid_cara(map[i][j]) == 2 && check)
					return (false);
				if (valid_cara(map[i][j]) == 2 && check == 0)
					check = find_player(game, i, j, map[i][j]);
			}
			else
				return (false);
		}
	}
	if (check != 1)
		return (false);
	return (true);
}

void	add_space(int size, char **map)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	while (map[i])
	{
		j = 0;
		dest = malloc(size + 1);
		while (map[i][j])
		{
			dest[j] = map[i][j];
			j++;
		}
		while (j < size)
			dest[j++] = ' ';
		dest[j] = '\0';
		free(map[i]);
		map[i] = dest;
		i++;
	}
}

bool	parssing_map(t_game *game, char *str)
{
	game->conf->map = ft_split(str, '\n');
	add_space(game->conf->map_width, game->conf->map);
	if (!check_caracter(game, game->conf->map))
		return (message_error(CRCTR), clean_tab(&game->conf->map), false);
	if (!check_walls(game->conf->map_height, game->conf->map))
		return (message_error(WALL), clean_tab(&game->conf->map), false);
	else
		return (true);
}
