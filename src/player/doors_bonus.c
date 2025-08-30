/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:58:43 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/23 11:45:13 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_doors	*check_player_door(double delta_x, double delta_y,
	int i, t_game *game)
{
	double	dir_to_door;
	double	player_dir;
	double	angle_diff;

	dir_to_door = atan2(delta_y, delta_x);
	player_dir = atan2(game->player.dir_y, game->player.dir_x);
	angle_diff = fabs(dir_to_door - player_dir);
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	angle_diff = fabs(angle_diff);
	if (angle_diff < M_PI / 4)
		return (&game->doors.doors[i]);
	return (NULL);
}

t_doors	*find_nearest_door(t_game *game)
{
	double	delta_x;
	double	delta_y;
	double	distance;
	int		i;

	i = 0;
	while (i < game->doors.count)
	{
		delta_x = game->doors.doors[i].x - game->player.pos_x;
		delta_y = game->doors.doors[i].y - game->player.pos_y;
		distance = sqrt(delta_x * delta_x + delta_y * delta_y);
		if (distance < game->doors.max_distance)
			return (check_player_door(delta_x, delta_y, i, game));
		i++;
	}
	return (NULL);
}

void	toggle_door(t_game *game, int door_x, int door_y)
{
	int	i;

	i = 0;
	while (i < game->doors.count)
	{
		if (game->doors.doors[i].x == door_x
			&& game->doors.doors[i].y == door_y)
		{
			if (game->doors.doors[i].state == 0)
			{
				game->doors.doors[i].state = 1;
				game->map.map[door_y][door_x] = DOOR_OPEN;
			}
			else
			{
				game->doors.doors[i].state = 0;
				game->map.map[door_y][door_x] = DOOR;
			}
			return ;
		}
		i++;
	}
}

void	interact_door(t_game *game)
{
	int		door_x;
	int		door_y;
	double	check_dist;
	char	cell_content;

	check_dist = 1.0;
	door_x = (int)(game->player.pos_x + game->player.dir_x * check_dist);
	door_y = (int)(game->player.pos_y + game->player.dir_y * check_dist);
	if (is_bounds(door_x, door_y, game))
	{
		cell_content = game->map.map[door_y][door_x];
		if (is_doors(cell_content))
			toggle_door(game, door_x, door_y);
	}
}
