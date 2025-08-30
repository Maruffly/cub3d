/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:01:32 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/21 15:24:05 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_directions(int *dx, int *dy)
{
	dx[0] = 1;
	dx[1] = -1;
	dx[2] = 0;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = 1;
	dy[3] = -1;
}

static void	try_direction(t_enemy_nav *nav, int nx, int ny)
{
	double	distance;
	double	player_x;
	double	player_y;

	if (!is_walkable(nav->game, nx, ny))
		return ;
	player_x = nav->game->player.pos_x;
	player_y = nav->game->player.pos_y;
	distance = get_distance(nx + 0.5, ny + 0.5, player_x, player_y);
	if (distance < nav->best->dist)
	{
		nav->best->dist = distance;
		nav->best->x = nx;
		nav->best->y = ny;
	}
}

static void	explore_directions(t_enemy_nav *nav, int *dx, int *dy)
{
	int	i;
	int	nx;
	int	ny;

	i = 0;
	while (i < 4)
	{
		nx = (int)(nav->enemy->x) + dx[i];
		ny = (int)(nav->enemy->y) + dy[i];
		try_direction(nav, nx, ny);
		i++;
	}
}

void	get_best_direction(t_game *game, t_enemy *enemy, t_best *best)
{
	int			dx[4];
	int			dy[4];
	t_enemy_nav	nav;

	init_directions(dx, dy);
	nav.game = game;
	nav.enemy = enemy;
	nav.best = best;
	explore_directions(&nav, dx, dy);
}

void	move_enemy_towards_player(t_game *game, t_enemy *enemy)
{
	t_best	best;
	double	speed;
	double	dir_x;
	double	dir_y;
	double	len;

	best.x = (int)enemy->x;
	best.y = (int)enemy->y;
	best.dist = get_distance(enemy->x, enemy->y,
			game->player.pos_x, game->player.pos_y);
	get_best_direction(game, enemy, &best);
	if (best.x == (int)enemy->x && best.y == (int)enemy->y)
		return ;
	dir_x = best.x + 0.5 - enemy->x;
	dir_y = best.y + 0.5 - enemy->y;
	len = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (len <= 0)
		return ;
	speed = 0.0125;
	enemy->x += (dir_x / len) * speed;
	enemy->y += (dir_y / len) * speed;
}
