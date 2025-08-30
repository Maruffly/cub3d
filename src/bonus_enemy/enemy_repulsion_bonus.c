/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_repulsion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:16:05 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/21 15:19:05 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	normalize_angle(double angle)
{
	while (angle < -M_PI)
		angle += 2 * M_PI;
	while (angle > M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

static t_vector	compute_vector(double from_x, double from_y,
	double to_x, double to_y)
{
	t_vector	vec;
	double		dx;
	double		dy;
	double		dist;

	dx = to_x - from_x;
	dy = to_y - from_y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist == 0)
	{
		vec.dir_x = 0;
		vec.dir_y = 0;
		vec.dist = 0;
		return (vec);
	}
	vec.dir_x = dx / dist;
	vec.dir_y = dy / dist;
	vec.dist = dist;
	return (vec);
}

void	repulse_enemy(t_game *game, t_enemy *enemy)
{
	t_vector	vec;
	double		strength;
	double		new_x;
	double		new_y;

	vec = compute_vector(game->player.pos_x, game->player.pos_y,
			enemy->x, enemy->y);
	if (vec.dist == 0)
		return ;
	strength = 0.7;
	new_x = enemy->x + vec.dir_x * strength;
	new_y = enemy->y + vec.dir_y * strength;
	if (check_position(new_x, enemy->y, game))
		enemy->x = new_x;
	if (check_position(enemy->x, new_y, game))
		enemy->y = new_y;
}
