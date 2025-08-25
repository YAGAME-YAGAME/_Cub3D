/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:22:17 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/30 18:17:34 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	check_name(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 5)
		return (false);
	if (name[len - 1] != 'b')
		return (false);
	if (name[len - 2] != 'u')
		return (false);
	if (name[len - 3] != 'c')
		return (false);
	if (name[len - 4] != '.')
		return (false);
	if (name[len - 5] == '/')
		return (false);
	return (true);
}

bool	path_name(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 5)
		return (false);
	if (name[len - 1] != 'm')
		return (false);
	if (name[len - 2] != 'p')
		return (false);
	if (name[len - 3] != 'x')
		return (false);
	if (name[len - 4] != '.')
		return (false);
	if (name[len - 5] == '/')
		return (false);
	return (true);
}
