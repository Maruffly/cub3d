/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:33:39 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/21 16:33:38 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_bounds(double x, double y, t_game *game)
{
	if (x >= game->map.map_width)
		return (false);
	if (y >= game->map.map_height)
		return (false);
	return (true);
}

static bool	has_wall_around(double x, double y, t_game *game)
{
	if (game->map.map[(int)(y + MARGIN)][(int)(x + MARGIN)] == WALL)
		return (true);
	if (game->map.map[(int)(y - MARGIN)][(int)(x + MARGIN)] == WALL)
		return (true);
	if (game->map.map[(int)(y + MARGIN)][(int)(x - MARGIN)] == WALL)
		return (true);
	if (game->map.map[(int)(y - MARGIN)][(int)(x - MARGIN)] == WALL)
		return (true);
	return (false);
}

static bool	collides_with_enemy(double x, double y, t_game *game)
{
	int		i;
	double	dx;
	double	dy;
	double	dist;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].is_alive)
		{
			dx = x - game->enemies[i].x;
			dy = y - game->enemies[i].y;
			dist = sqrt(dx * dx + dy * dy);
			if (dist < 0.25)
				return (true);
		}
		i++;
	}
	return (false);
}

bool	check_position(double x, double y, t_game *game)
{
	if (!is_bounds(x, y, game))
		return (false);
	if (game->map.map[(int)y][(int)x] == WALL
		|| game->map.map[(int)y][(int)x] == DOOR)
		return (false);
	if (has_wall_around(x, y, game))
		return (false);
	if (collides_with_enemy(x, y, game))
		return (false);
	return (true);
}

bool	is_valid_pos(double new_x, double new_y, t_game *game)
{
	bool	has_moved;

	has_moved = false;
	if (check_position(new_x, game->player.pos_y, game))
	{
		game->player.pos_x = new_x;
		has_moved = true;
	}
	if (check_position(game->player.pos_x, new_y, game))
	{
		game->player.pos_y = new_y;
		has_moved = true;
	}
	return (has_moved);
}
