/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:00:00 by yagame            #+#    #+#             */
/*   Updated: 2025/08/27 17:04:25 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	set_texture_path(char **texture_path, char *path)
{
	if (*texture_path != NULL)
		return (0); // Texture already set
	*texture_path = ft_strdup(path);
	if (!*texture_path)
		return (0);
	return (1);
}

int	parse_texture(t_game *game, char *line)
{
	char	*trimmed;
	char	*path;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
	{
		path = trim_whitespace(trimmed + 3);
		if (!path || !set_texture_path(&game->conf->no_texture_path, path))
		{
			free(trimmed);
			free(path);
			return (0);
		}
		free(path);
	}
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
	{
		path = trim_whitespace(trimmed + 3);
		if (!path || !set_texture_path(&game->conf->so_texture_path, path))
		{
			free(trimmed);
			free(path);
			return (0);
		}
		free(path);
	}
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
	{
		path = trim_whitespace(trimmed + 3);
		if (!path || !set_texture_path(&game->conf->we_texture_path, path))
		{
			free(trimmed);
			free(path);
			return (0);
		}
		free(path);
	}
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
	{
		path = trim_whitespace(trimmed + 3);
		if (!path || !set_texture_path(&game->conf->ea_texture_path, path))
		{
			free(trimmed);
			free(path);
			return (0);
		}
		free(path);
	}
	else
	{
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}
