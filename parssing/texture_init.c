/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 23:08:53 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/30 18:18:48 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	no_init(t_config *game, char *path)
{
	char	*str;

	str = remove_nline(path);
	game->no_texture_path = str;
	return (true);
	free(str);
	return (false);
}

bool	so_init(t_config *game, char *path)
{
	char	*str;

	str = remove_nline(path);
	game->so_texture_path = str;
	return (true);
	free(str);
	return (false);
}

bool	we_init(t_config *game, char *path)
{
	char	*str;

	str = remove_nline(path);
	game->we_texture_path = str;
	return (true);
	free(str);
	return (false);
}

bool	ea_init(t_config *game, char *path)
{
	char	*str;

	str = remove_nline(path);
	game->ea_texture_path = str;
	return (true);
	free(str);
	return (false);
}

bool	text_init(t_config *game, char *line)
{
	char	**tb_text;

	tb_text = ft_split(line, ' ');
	if (!tb_text)
		return (false);
	if (size_tab(tb_text) > 2)
		return (clean_tab(&tb_text), false);
	if (tb_text[0] && tb_text[1] && !ft_strcmp(tb_text[0], "NO"))
	{
		if (!no_init(game, tb_text[1]))
			return (clean_tab(&tb_text), false);
	}
	else if (tb_text[0] && tb_text[1] && !ft_strcmp(tb_text[0], "SO"))
	{
		if (!so_init(game, tb_text[1]))
			return (clean_tab(&tb_text), false);
	}
	else if (tb_text[0] && tb_text[1] && !ft_strcmp(tb_text[0], "WE"))
	{
		if (!we_init(game, tb_text[1]))
			return (clean_tab(&tb_text), false);
	}
	else if (tb_text[0] && tb_text[1] && !ft_strcmp(tb_text[0], "EA"))
	{
		if (!ea_init(game, tb_text[1]))
			return (clean_tab(&tb_text), false);
	}
	else
		return (false);
	return (clean_tab(&tb_text), true);
}
