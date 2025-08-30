/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:39:06 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/23 11:41:16 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_xpm_file(char *filename)
{
	int	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	return (len > 4 && ft_strncmp(filename + len - 4, ".xpm", 4) == 0);
}

bool	is_dir(char *arg)
{
	int	fd;

	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (true);
	}
	return (false);
}

int	parse_extension(char *filename)
{
	int	fd;
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg("Cannot opening file"));
	close(fd);
	return (1);
}

void	check_and_store_path(char **dest, char *path, t_game *game)
{
	char	*dup;

	dup = ft_strdup(path);
	if (!dup || !is_valid_xpm(dup))
	{
		if (dup)
			free(dup);
		error_msg("Invalid or missing texture file (.xpm)");
		exit_parse_error(game);
	}
	*dest = dup;
}

void	check_texture_split_errors(char **split, t_game *game)
{
	if (!split || !split[0] || !split[1])
	{
		if (split)
			free_split(split);
		error_msg("Texture line format invalid");
		exit_parse_error(game);
	}
	if (!is_valid_xpm(split[1]))
	{
		free_split(split);
		error_msg("Invalid or missing texture file (.xpm)");
		exit_parse_error(game);
	}
}
