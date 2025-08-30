/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_load.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:49:25 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/21 16:28:59 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*read_file_content(int fd)
{
	char	buffer[BUFFER + 1];
	char	*content;
	char	*tmp;
	int		bytes;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	bytes = read(fd, buffer, BUFFER);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		tmp = ft_strjoin(content, buffer);
		free(content);
		if (!tmp)
			return (NULL);
		content = tmp;
		bytes = read(fd, buffer, BUFFER);
	}
	if (bytes < 0)
		return (free(content), NULL);
	return (content);
}

int	read_lines(t_game *game, int fd)
{
	char	*content;

	content = read_file_content(fd);
	if (!content)
		return (error_msg("Reading file failed"));
	free_split(game->map.file);
	game->map.file = ft_split(content, '\n');
	free(content);
	if (!game->map.file)
		return (error_msg("Split failed"));
	return (0);
}

int	read_map(t_game *game)
{
	int		fd;
	int		res;
	char	**file;

	file = ft_calloc(game->map.line_count + 1, sizeof(char *));
	if (!file)
		return (error_msg("Memory allocation failed for map file"));
	game->map.file = file;
	fd = open(game->map.path, O_RDONLY);
	if (fd < 0)
		return (error_msg("Failed to open map file"));
	res = read_lines(game, fd);
	close(fd);
	return (res);
}

int	get_lines(char *path)
{
	int		fd;
	char	buffer[BUFFER];
	ssize_t	bytes_read;
	int		newlines;

	newlines = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER);
	while (bytes_read > 0)
	{
		newlines += count_newlines_in_buffer(buffer, bytes_read);
		bytes_read = read(fd, buffer, BUFFER);
	}
	close(fd);
	if (bytes_read < 0)
		return (-1);
	return (newlines + 1);
}

int	load_map(t_game *game)
{
	game->map.line_count = get_lines(game->map.path);
	if (game->map.line_count <= 0)
		return (error_msg("Empty or invalid .cub file"));
	if (read_map(game) != 0)
		return (1);
	return (0);
}
