/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:07:41 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/23 12:17:36 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_button_handler(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		game->weapon_anim = true;
		game->weapon_anim_counter = 0;
	}
	return (0);
}

int	mouse_move_handler(int x, int y, t_game *game)
{
	static int	prev_x;
	int			diff;
	double		rot_speed;

	(void)y;
	if (prev_x == -1)
	{
		prev_x = x;
		return (0);
	}
	diff = x - prev_x;
	if (diff != 0)
	{
		rot_speed = 0.05;
		rot_speed *= diff;
		rotate_player(game, rot_speed);
		mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
		prev_x = WIDTH / 2;
	}
	return (0);
}
