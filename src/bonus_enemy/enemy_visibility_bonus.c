/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_visibility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:39:44 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/21 15:19:19 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_within_fov(t_game *game, double dx, double dy)
{
	double	player_angle;
	double	angle_to_enemy;
	double	angle_diff;
	double	fov;
	double	margin;

	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	angle_to_enemy = atan2(dy, dx);
	angle_diff = normalize_angle(angle_to_enemy - player_angle);
	fov = M_PI / 3.0;
	margin = 0.2;
	if (fabs(angle_diff) > (fov / 2.0 + margin))
		return (false);
	return (true);
}

static bool	is_wall_or_door(t_game *game, double x, double y)
{
	char	tile;

	tile = game->map.map[(int)y][(int)x];
	if (tile == '1' || tile == 'D')
		return (true);
	return (false);
}

static bool	scan_line_of_sight(t_game *game, double x_step,
	double y_step, double steps)
{
	double	x;
	double	y;
	int		i;

	x = game->player.pos_x;
	y = game->player.pos_y;
	i = 0;
	while (i < (int)steps)
	{
		if (is_wall_or_door(game, x, y))
			return (false);
		x += x_step;
		y += y_step;
		i++;
	}
	return (true);
}

static bool	has_line_of_sight(t_game *game, double dx, double dy, double dist)
{
	double	steps;
	double	x_step;
	double	y_step;

	steps = dist * 10.0;
	x_step = dx / steps;
	y_step = dy / steps;
	return (scan_line_of_sight(game, x_step, y_step, steps));
}

bool	is_enemy_visible(t_game *game, t_enemy *enemy)
{
	double	distance;
	double	dx;
	double	dy;

	dx = enemy->x - game->player.pos_x;
	dy = enemy->y - game->player.pos_y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance < 0.1)
		return (false);
	if (!is_within_fov(game, dx, dy))
		return (false);
	if (!has_line_of_sight(game, dx, dy, distance))
		return (false);
	return (true);
}
