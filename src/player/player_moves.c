/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:52:29 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/21 17:13:06 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * MOVESPEED;
	new_y = game->player.pos_y + game->player.dir_y * MOVESPEED;
	return (is_valid_pos(new_x, new_y, game));
}

int	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * MOVESPEED;
	new_y = game->player.pos_y - game->player.dir_y * MOVESPEED;
	return (is_valid_pos(new_x, new_y, game));
}

int	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_y * MOVESPEED;
	new_y = game->player.pos_y + game->player.dir_x * MOVESPEED;
	return (is_valid_pos(new_x, new_y, game));
}

int	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_y * MOVESPEED;
	new_y = game->player.pos_y - game->player.dir_x * MOVESPEED;
	return (is_valid_pos(new_x, new_y, game));
}

int	process_movement_inputs(t_game *game)
{
	int	has_moved;

	has_moved = 0;
	if (game->player.move_y == 1)
		has_moved = move_forward(game);
	if (game->player.move_y == -1)
		has_moved = move_backward(game);
	if (game->player.move_x == 1)
		has_moved = move_left(game);
	if (game->player.move_x == -1)
		has_moved = move_right(game);
	if (game->player.rotate)
		has_moved = rotate_player(game, game->player.rotate);
	return (has_moved);
}
