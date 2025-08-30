/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:07:46 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/21 17:12:54 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_vector(double *x, double *y, double angle)
{
	double	tmp_x;

	tmp_x = *x;
	*x = *x * cos(angle) - *y * sin(angle);
	*y = tmp_x * sin(angle) + *y * cos(angle);
}

bool	rotate_player(t_game *game, double rotdir)
{
	double	rot_speed;

	rot_speed = rotdir * ROTSPEED;
	rotate_vector(&game->player.dir_x, &game->player.dir_y, rot_speed);
	rotate_vector(&game->player.plane_x, &game->player.plane_y, rot_speed);
	return (true);
}

int	move(t_game *game)
{
	int			has_moved;
	int			cur_px;
	int			cur_py;
	static int	last_px = -1;
	static int	last_py = -1;

	has_moved = process_movement_inputs(game);
	if (has_moved)
	{
		cur_px = (int)game->player.pos_x;
		cur_py = (int)game->player.pos_y;
		if (cur_px != last_px || cur_py != last_py)
		{
			last_px = cur_px;
			last_py = cur_py;
		}
	}
	return (has_moved);
}
