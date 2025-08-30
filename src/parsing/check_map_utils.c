/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorislaine <jorislaine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:58:09 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/20 01:40:13 by jorislaine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	find_map_bounds_and_check_end(t_game *game, int *start,
	int *end, int *line_count)
{
	int		i;
	char	**file;

	file = game->map.file;
	*start = game->map.map_start;
	*end = *start;
	i = *start;
	while (file[*end] && (is_map_line(file[*end]) || is_empty_line(file[*end])))
		(*end)++;
	i = *end;
	while (file[i])
	{
		if (!is_empty_line(file[i]))
			return (error_msg("Map is not the last element in file"));
		i++;
	}
	*line_count = *end - *start;
	return (0);
}

static int	copy_map_and_calculate_width(t_game *game,
	int start, int line_count)
{
	int		i;
	int		len;
	int		max_width;
	char	**map;

	i = 0;
	max_width = 0;
	map = ft_calloc(line_count + 1, sizeof(char *));
	if (!map)
		return (error_msg("Map allocation failed"));
	while (i < line_count)
	{
		map[i] = ft_strdup(game->map.file[start + i]);
		if (!map[i])
			return (free_split(map), error_msg("Map copy failed"));
		len = ft_strlen(map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	map[i] = NULL;
	game->map.map = map;
	game->map.map_height = line_count;
	game->map.map_width = max_width;
	return (0);
}

int	extract_map_only(t_game *game)
{
	int	start;
	int	end;
	int	line_count;
	int	status;

	status = find_map_bounds_and_check_end(game, &start, &end, &line_count);
	if (status != 0)
		return (1);
	return (copy_map_and_calculate_width(game, start, line_count));
}

static int	surrounded_by_walls(char **grid, int row, int col, int map_height)
{
	int	len_current;
	int	len_above;
	int	len_below;

	len_current = ft_strlen(grid[row]);
	if (row == 0 || row == map_height - 1)
		return (1);
	if (col == 0 || col >= len_current - 1)
		return (1);
	if (!grid[row][col + 1] || grid[row][col + 1] == ' ')
		return (1);
	if (col > 0 && grid[row][col - 1] == ' ')
		return (1);
	if (!grid[row - 1])
		return (1);
	len_above = ft_strlen(grid[row - 1]);
	if (col >= len_above || grid[row - 1][col] == ' ')
		return (1);
	if (!grid[row + 1])
		return (1);
	len_below = ft_strlen(grid[row + 1]);
	if (col >= len_below || grid[row + 1][col] == ' ')
		return (1);
	return (0);
}

int	parse_map_walls(t_map *map)
{
	int		row;
	int		col;
	char	**grid;
	char	c;

	row = 0;
	grid = map->map;
	while (row < map->map_height)
	{
		col = 0;
		while (grid[row][col])
		{
			c = grid[row][col];
			if (c != '1' && c != ' ')
			{
				if (surrounded_by_walls(grid, row, col, map->map_height))
					return (1);
			}
			col++;
		}
		row++;
	}
	return (0);
}
