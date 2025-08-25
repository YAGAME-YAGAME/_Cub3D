/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:49:32 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/30 18:17:10 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	scan_number(char *str, int *index)
{
	char	buffer[10];
	int		i;
	int		j;
	int		color;

	i = 0;
	j = *index;
	while (str[j] && ft_isdigit(str[j]))
		buffer[i++] = str[j++];
	buffer[i] = 0;
	if (ft_strlen(buffer) > 3 || (str[j] != ',' && str[j] != 0))
		return (-1);
	color = ft_atoi(buffer);
	if (color > 255)
		return (-1);
	*index = j;
	return (color);
}

int	parss_number_color(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	r = scan_number(line, &i);
	i++;
	g = scan_number(line, &i);
	i++;
	b = scan_number(line, &i);
	if (line[i] != 0 || r < 0 || b < 0 || g < 0)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

bool	parss_color(t_config *game, char **str)
{
	char	*new;

	if (!ft_strcmp(str[0], "F"))
	{
		new = remove_nline(str[1]);
		game->floor_color = parss_number_color(new);
		free(new);
		if (game->floor_color < 0)
			return (false);
		return (true);
	}
	else if (!ft_strcmp(str[0], "C"))
	{
		new = remove_nline(str[1]);
		game->ceiling_color = parss_number_color(new);
		free(new);
		if (game->ceiling_color < 0)
			return (false);
		return (true);
	}
	else
		return (false);
}

bool	color_init(t_config *game, char *str)
{
	char	**tab;

	tab = ft_split(str, ' ');
	if (!tab)
		return (false);
	if (size_tab(tab) != 2)
		return (clean_tab(&tab), false);
	if (!parss_color(game, tab))
		return (clean_tab(&tab), false);
	return (true);
}
