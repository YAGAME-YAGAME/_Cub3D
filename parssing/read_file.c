/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:00:00 by yagame            #+#    #+#             */
/*   Updated: 2025/08/27 17:04:25 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	**read_file_lines(char *filename, int *line_count)
{
	int		fd;
	char	**lines;
	char	*line;
	int		i;

	*line_count = count_lines_in_file(filename);
	if (*line_count <= 0)
		return (NULL);
	
	lines = malloc(sizeof(char *) * (*line_count + 1));
	if (!lines)
		return (NULL);
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(lines);
		return (NULL);
	}
	
	i = 0;
	while ((line = get_next_line(fd)) != NULL && i < *line_count)
	{
		lines[i] = line;
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}
