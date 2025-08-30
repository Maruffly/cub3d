/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:26:20 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/22 13:54:28 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	process_enemy_proximity(t_game *game, int i, double *closest,
	double *last_attack_time)
{
	double			dx;
	double			dy;
	double			dist;
	static double	current_time;

	dx = game->player.pos_x - game->enemies[i].x;
	dy = game->player.pos_y - game->enemies[i].y;
	dist = sqrt(dx * dx + dy * dy);
	current_time += 0.016;
	if (dist < *closest)
	*closest = dist;
	if (game->weapon_anim && dist < game->proximity_threshold * 1.5)
		repulse_enemy(game, &game->enemies[i]);
	if (dist < game->proximity_threshold && current_time
		- *last_attack_time > 2.0)
	{
	game->screen_red = true;
	*last_attack_time = current_time;
	game->attack_counter++;
	}
	if (game->screen_red && current_time - *last_attack_time > 0.2)
	game->screen_red = false;
}

void	check_enemy_proximity(t_game *game)
{
	int				i;
	double			closest;
	static double	last_attack_time;

	i = 0;
	closest = 999.0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].is_alive)
			process_enemy_proximity(game, i, &closest, &last_attack_time);
		i++;
	}
}

static void	count_enemies(t_game *game)
{
	int	y;
	int	x;

	game->enemy_count = 0;
	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (game->map.map[y][x] == 'X')
				game->enemy_count++;
			x++;
		}
		y++;
	}
}

static void	setup_enemy_at(t_game *game, int i, int j, int *k)
{
	t_enemy	*enemy;

	enemy = &game->enemies[*k];
	enemy->x = j + 0.5;
	enemy->y = i + 0.5;
	enemy->speed = 0.009;
	enemy->is_alive = true;
	enemy->visible = true;
	enemy->targeted = false;
	load_texture(game, "assets/omar.xpm", &enemy->texture);
	(*k)++;
}

void	init_enemies(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	count_enemies(game);
	game->enemies = ft_calloc(game->enemy_count, sizeof(t_enemy));
	if (!game->enemies)
		exit_cub3d(game);
	i = -1;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
		{
			if (game->map.map[i][j] == 'X')
				setup_enemy_at(game, i, j, &k);
		}
	}
}
