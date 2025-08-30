/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorislaine <jorislaine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:28:40 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/20 01:43:28 by jorislaine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (0);
	if (line[i] == '1' || line[i] == '0')
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != 'O' && line[i] != 'D')
			return (0);
		i++;
	}
	return (1);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	parse_config(t_game *game)
{
	int	i;
	int	ret;

	i = 0;
	while (game->map.file[i] && !is_map_line(game->map.file[i]))
	{
		if (is_empty_line(game->map.file[i]))
		{
			i++;
			continue ;
		}
		ret = 1;
		if (is_texture_line(game->map.file[i]))
			ret = parse_texture_line(game, game->map.file[i]);
		else if (is_color_line(game->map.file[i]))
			ret = parse_color_line(game, game->map.file[i]);
		if (ret != 0)
			return (error_msg("Invalid line in config"));
		i++;
	}
	game->map.map_start = i;
	return (0);
}
