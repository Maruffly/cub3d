/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorislaine <jorislaine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:57:53 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/20 00:57:00 by jorislaine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	get_distance(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

bool	is_walkable(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || y >= game->map.map_height
		|| x >= (int)ft_strlen(game->map.map[y]))
		return (false);
	if (game->map.map[y][x] == '1' || game->map.map[y][x] == 'D')
		return (false);
	return (true);
}

void	init_ray_step(t_game *game, t_enemy *enemy,
	double *dx, double *dy)
{
	double	dist;
	double	tmp_dx;
	double	tmp_dy;
	double	steps;

	tmp_dx = enemy->x - game->player.pos_x;
	tmp_dy = enemy->y - game->player.pos_y;
	dist = sqrt(tmp_dx * tmp_dx + tmp_dy * tmp_dy);
	if (dist == 0)
	{
		*dx = 0;
		*dy = 0;
		return ;
	}
	steps = dist * 10;
	*dx = tmp_dx / steps;
	*dy = tmp_dy / steps;
}

static void	compute_enemy_distances(t_game *game)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < game->enemy_count)
	{
		dx = game->player.pos_x - game->enemies[i].x;
		dy = game->player.pos_y - game->enemies[i].y;
		game->enemies[i].distance = dx * dx + dy * dy;
		i++;
	}
}

void	sort_enemies_by_distance(t_game *game)
{
	int		i;
	int		j;
	t_enemy	tmp;

	compute_enemy_distances(game);
	i = 0;
	while (i < game->enemy_count - 1)
	{
		j = 0;
		while (j < game->enemy_count - i - 1)
		{
			if (game->enemies[j].distance < game->enemies[j + 1].distance)
			{
				tmp = game->enemies[j];
				game->enemies[j] = game->enemies[j + 1];
				game->enemies[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
