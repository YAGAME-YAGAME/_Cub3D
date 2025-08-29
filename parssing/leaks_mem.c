/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:00:00 by yagame            #+#    #+#             */
/*   Updated: 2025/08/27 17:04:25 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->conf)
	{
		if (game->conf->no_texture_path)
			free(game->conf->no_texture_path);
		if (game->conf->so_texture_path)
			free(game->conf->so_texture_path);
		if (game->conf->we_texture_path)
			free(game->conf->we_texture_path);
		if (game->conf->ea_texture_path)
			free(game->conf->ea_texture_path);
		if (game->conf->map)
			free_split(game->conf->map);
		free(game->conf);
	}
}
