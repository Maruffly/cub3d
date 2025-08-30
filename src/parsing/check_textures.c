/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:43:04 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/23 11:41:58 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_color_line(char *line)
{
	return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0);
}

int	is_rgb_valid(char **rgb, int *values)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!ft_isdigit_str(rgb[i]))
			return (0);
		values[i] = ft_atoi(rgb[i]);
		if (values[i] < 0 || values[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

int	parse_texture_line(t_game *game, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	check_texture_split_errors(split, game);
	if (ft_strncmp(split[0], "NO", 3) == 0)
		check_and_store_path(&game->tex_paths.north, split[1], game);
	else if (ft_strncmp(split[0], "SO", 3) == 0)
		check_and_store_path(&game->tex_paths.south, split[1], game);
	else if (ft_strncmp(split[0], "WE", 3) == 0)
		check_and_store_path(&game->tex_paths.west, split[1], game);
	else if (ft_strncmp(split[0], "EA", 3) == 0)
		check_and_store_path(&game->tex_paths.east, split[1], game);
	else
		return (free_split(split), 1);
	return (free_split(split), 0);
}

int	parse_color_line(t_game *game, char *line)
{
	char	**rgb;
	char	*clean;
	char	**split;
	int		values[3];

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
		return (free_split(split), 1);
	clean = ft_strtrim(split[1], "\n");
	free(split[1]);
	split[1] = clean;
	rgb = ft_split(split[1], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), free_split(split), 1);
	if (!is_rgb_valid(rgb, values))
		return (free_split(rgb), free_split(split), 1);
	if (split[0][0] == 'F')
		game->color.floor = (values[0] << 16) | (values[1] << 8) | values[2];
	else if (split[0][0] == 'C')
		game->color.sky = (values[0] << 16) | (values[1] << 8) | values[2];
	else
		return (free_split(rgb), free_split(split), 1);
	free_split(rgb);
	return (free_split(split), 0);
}
