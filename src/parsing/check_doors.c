/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:20:48 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/22 16:53:26 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_door_if_needed(t_game *game, int x, int y, int *count)
{
	if (x < game->map.map_width && is_doors(game->map.map[y][x]))
	{
		game->doors.doors[*count].x = x;
		game->doors.doors[*count].y = y;
		game->doors.max_distance = 1.5;
		if (game->map.map[y][x] == DOOR_OPEN)
			game->doors.doors[*count].state = 1;
		else
			game->doors.doors[*count].state = 0;
		(*count)++;
	}
}

void	init_each_door(t_game *game)
{
	int	x;
	int	y;
	int	count;
	int	line_length;

	y = 0;
	count = 0;
	while (y < game->map.map_height)
	{
		x = 0;
		line_length = ft_strlen(game->map.map[y]);
		while (x < line_length)
		{
			init_door_if_needed(game, x, y, &count);
			x++;
		}
		y++;
	}
}

static int	count_doors_in_map(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map.map_height)
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (game->map.map[y][x] == DOOR || game->map.map[y][x] == DOOR_OPEN)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	count_doors(t_game *game)
{
	int	count;

	count = count_doors_in_map(game);
	game->doors.count = count;
	game->doors.capacity = count;
	if (count > 0)
	{
		game->doors.doors = calloc(count, sizeof(t_doors));
		if (!game->doors.doors)
			exit_parse_error(game);
	}
	else
		game->doors.doors = NULL;
}
