/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_direction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:50:25 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/09 14:12:49 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player_north(char dir, t_game *game)
{
	if (dir == 'N')
	{
		game->player.dir = NORTH;
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else
		return ;
}

void	init_player_south(char dir, t_game *game)
{
	if (dir == 'S')
	{
		game->player.dir = SOUTH;
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else
		return ;
}

void	init_player_east(char dir, t_game *game)
{
	if (dir == 'E')
	{
		game->player.dir = EAST;
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else
		return ;
}

void	init_player_west(char dir, t_game *game)
{
	if (dir == 'W')
	{
		game->player.dir = WEST;
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
	else
		return ;
}

void	init_player_dir(char dir, t_game *game)
{
	init_player_north(dir, game);
	init_player_south(dir, game);
	init_player_east(dir, game);
	init_player_west(dir, game);
}
