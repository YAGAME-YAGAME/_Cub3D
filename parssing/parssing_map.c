/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:00:00 by yagame            #+#    #+#             */
/*   Updated: 2025/08/27 17:04:25 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	is_map_line(char *line)
{
	int	i;

	if (!line || is_empty_line(line))
		return (0);
	i = 0;
	while (line[i])
	{
		if (!is_valid_map_char(line[i]) && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	find_map_start(char **lines, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		if (is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	calculate_map_dimensions(char **lines, int start, int line_count, int *height, int *width)
{
	int	i;
	int	len;

	*height = 0;
	*width = 0;
	i = start;
	while (i < line_count)
	{
		if (lines[i] && !is_empty_line(lines[i]))
		{
			len = ft_strlen(lines[i]);
			if (lines[i][len - 1] == '\n')
				len--;
			if (len > *width)
				*width = len;
			(*height)++;
		}
		else if (*height > 0)
			break; // End of map
		i++;
	}
	return (*height > 0 && *width > 0);
}

int	parse_map_lines(t_game *game, char **lines, int start_index)
{
	int		i, j;
	int		map_line;
	char	*line;

	game->conf->map = malloc(sizeof(char *) * (game->conf->map_height + 1));
	if (!game->conf->map)
		return (0);
	
	map_line = 0;
	i = start_index;
	while (i < start_index + game->conf->map_height && lines[i])
	{
		if (!is_empty_line(lines[i]))
		{
			line = malloc(game->conf->map_width + 1);
			if (!line)
				return (0);
			
			j = 0;
			while (j < game->conf->map_width)
			{
				if (j < (int)ft_strlen(lines[i]) && lines[i][j] != '\n')
					line[j] = lines[i][j];
				else
					line[j] = ' ';
				j++;
			}
			line[game->conf->map_width] = '\0';
			game->conf->map[map_line] = line;
			map_line++;
		}
		i++;
	}
	game->conf->map[map_line] = NULL;
	return (1);
}

static int	validate_textures_and_colors(t_game *game)
{
	if (!game->conf->no_texture_path || !game->conf->so_texture_path ||
		!game->conf->we_texture_path || !game->conf->ea_texture_path)
	{
		message_error("Missing texture paths");
		return (0);
	}
	if (game->conf->floor_color == -1 || game->conf->ceiling_color == -1)
	{
		message_error("Missing floor or ceiling color");
		return (0);
	}
	return (1);
}

static int	parse_config_lines(t_game *game, char **lines, int map_start)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (i < map_start)
	{
		if (!is_empty_line(lines[i]))
		{
			trimmed = trim_whitespace(lines[i]);
			if (trimmed && ft_strlen(trimmed) > 0)
			{
				if (!parse_texture(game, trimmed) && !parse_color(game, trimmed))
				{
					free(trimmed);
					message_error("Invalid configuration line");
					return (0);
				}
			}
			free(trimmed);
		}
		i++;
	}
	return (validate_textures_and_colors(game));
}

int	parssing_map(t_game *game, char *file_name)
{
	char	**lines;
	int		line_count;
	int		map_start;

	// Check file extension
	if (!check_file_name(file_name))
		message_error("Invalid file extension. Must be .cub");
	
	// Read all lines from file
	lines = read_file_lines(file_name, &line_count);
	if (!lines)
		message_error("Cannot read file or file is empty");
	
	// Find where the map starts
	map_start = find_map_start(lines, line_count);
	if (map_start == -1)
	{
		free_split(lines);
		message_error("No valid map found in file");
	}
	
	// Parse configuration lines (textures and colors)
	if (!parse_config_lines(game, lines, map_start))
	{
		free_split(lines);
		return (0);
	}
	
	// Calculate map dimensions
	if (!calculate_map_dimensions(lines, map_start, line_count, 
		&game->conf->map_height, &game->conf->map_width))
	{
		free_split(lines);
		message_error("Invalid map dimensions");
	}
	
	// Parse map lines
	if (!parse_map_lines(game, lines, map_start))
	{
		free_split(lines);
		message_error("Failed to parse map");
	}
	
	// Find and validate player position
	if (!find_player(game))
	{
		free_split(lines);
		message_error("Map must contain exactly one player (N, S, E, or W)");
	}
	
	// Check if map is properly enclosed by walls
	if (!check_map_walls(game))
	{
		free_split(lines);
		message_error("Map must be surrounded by walls");
	}
	
	free_split(lines);
	return (1);
}
