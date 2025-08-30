/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:00:55 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/22 16:55:03 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_map_char(t_map *map)
{
	int		row;
	int		col;
	char	**grid;
	int		player_count;

	row = 0;
	grid = map->map;
	player_count = 0;
	while (row < map->map_height)
	{
		col = 0;
		while (grid[row][col])
		{
			if (!is_valid_map_char(grid[row][col]))
				return (1);
			if (is_player_char(grid[row][col]))
				player_count++;
			col++;
		}
		row++;
	}
	if (player_count != 1)
		return (1);
	return (0);
}

int	check_map_is_at_the_end(t_map *map)
{
	int	i;
	int	start;

	start = map->map_start + map->map_height;
	i = start;
	while (map->file[i])
	{
		if (!is_empty_line(map->file[i]))
			return (1);
		i++;
	}
	return (0);
}

int	init_player_from_map(t_game *game)
{
	int		row;
	int		col;
	char	**map;

	map = game->map.map;
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == 'N' || map[row][col] == 'S' ||
				map[row][col] == 'E' || map[row][col] == 'W')
			{
				game->player.pos_x = (double)col + 0.5;
				game->player.pos_y = (double)row + 0.5;
				init_player_dir(map[row][col], game);
				map[row][col] = '0';
				return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}

bool	is_valid_enemy_count(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (game->map.map[y][x] == 'X')
			{
				count++;
				if (count > 50)
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

int	validate_map(t_game *game)
{
	if (!game->map.map || game->map.map_height == 0)
		return (error_msg("No valid map found"));
	if (parse_map_walls(&game->map) != 0)
		return (error_msg("Map is not closed"));
	if (parse_map_char(&game->map) != 0)
		return (error_msg("Invalid map player or char"));
	if (init_player_from_map(game) != 0)
		return (error_msg("No valid player start position"));
	if (check_map_is_at_the_end(&game->map) != 0)
		return (error_msg("Map is not the last element in file"));
	if (!is_valid_enemy_count(game))
	{
		error_msg("Too many enemies (max 3)");
		free_parsing_data(game);
		exit(1);
	}
	return (0);
}
