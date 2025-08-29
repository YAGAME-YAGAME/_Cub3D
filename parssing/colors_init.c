/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:00:00 by yagame            #+#    #+#             */
/*   Updated: 2025/08/27 17:04:25 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	validate_rgb_value(int value)
{
	return (value >= 0 && value <= 255);
}

static int	parse_rgb_values(char *rgb_str, int *r, int *g, int *b)
{
	char	**rgb_split;
	int		result;

	rgb_split = ft_split(rgb_str, ',');
	if (!rgb_split || !rgb_split[0] || !rgb_split[1] || !rgb_split[2] || rgb_split[3])
	{
		free_split(rgb_split);
		return (0);
	}
	
	*r = ft_atoi(rgb_split[0]);
	*g = ft_atoi(rgb_split[1]);
	*b = ft_atoi(rgb_split[2]);
	
	result = validate_rgb_value(*r) && validate_rgb_value(*g) && validate_rgb_value(*b);
	free_split(rgb_split);
	return (result);
}

static uint32_t	rgb_to_hex(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

int	parse_color(t_game *game, char *line)
{
	char	*trimmed;
	char	*color_str;
	int		r, g, b;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	
	if (ft_strncmp(trimmed, "F ", 2) == 0)
	{
		if (game->conf->floor_color != -1)
		{
			free(trimmed);
			return (0); // Floor color already set
		}
		color_str = trim_whitespace(trimmed + 2);
		if (!color_str || !parse_rgb_values(color_str, &r, &g, &b))
		{
			free(trimmed);
			free(color_str);
			return (0);
		}
		game->conf->floor_color = rgb_to_hex(r, g, b);
		free(color_str);
	}
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
	{
		if (game->conf->ceiling_color != -1)
		{
			free(trimmed);
			return (0); // Ceiling color already set
		}
		color_str = trim_whitespace(trimmed + 2);
		if (!color_str || !parse_rgb_values(color_str, &r, &g, &b))
		{
			free(trimmed);
			free(color_str);
			return (0);
		}
		game->conf->ceiling_color = rgb_to_hex(r, g, b);
		free(color_str);
	}
	else
	{
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}
