/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:48:34 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/27 16:37:42 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	**map_vertical(int size, char **map)
{
	int		i;
	int		j;
	int		len;
	char	**new;

	i = 0;
	len = ft_strlen(map[0]);
	new = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		j = 0;
		new[i] = malloc(size + 1);
		while (j < size)
		{
			new[i][j] = map[j][i];
			j++;
		}
		new[i][j] = '\0';
		i++;
	}
	new[i] = NULL;
	return (new);
}

bool	check_line(char *str)
{
	char	**split_line;
	int		i;
	int		len;

	i = 0;
	split_line = ft_split(str, ' ');
	if (!split_line)
		return (false);
	while (split_line[i])
	{
		len = ft_strlen(split_line[i]);
		if (split_line[i][0] != '1' || split_line[i][len - 1] != '1')
		{
			clean_tab(&split_line);
			return (false);
		}
		i++;
	}
	clean_tab(&split_line);
	return (true);
}

bool	check_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (!check_line(map[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_walls(int size, char **map)
{
	char	**vertical;

	vertical = map_vertical(size, map);
	if (!check_map(vertical) || !check_map(map))
	{
		clean_tab(&vertical);
		return (false);
	}
	clean_tab(&vertical);
	return (true);
}
