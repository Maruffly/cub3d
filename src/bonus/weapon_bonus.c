/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:01:29 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/22 14:25:52 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	get_animation_angle(t_game *game)
{
	double	angle;

	angle = sin(game->weapon_anim_counter * 1.0) * 5.0;
	game->weapon_anim_counter++;
	if (game->weapon_anim_counter >= game->weapon_anim_frames)
	{
		game->weapon_anim = false;
		game->weapon_anim_counter = 0;
	}
	return (angle);
}

double	calculate_weapon_animation(t_game *game)
{
	double			angle;
	static double	last_animation_time = 0;
	static double	current_time = 0;

	angle = 0.0;
	current_time += 0.016;
	last_animation_time = 0;
	if (game->weapon_anim && game->weapon_anim_counter == 0)
	{
		if (current_time - last_animation_time < 1.0)
		{
			game->weapon_anim = false;
			return (angle);
		}
		else
			last_animation_time = current_time;
	}
	if (!game->weapon_anim)
		return (angle);
	return (get_animation_angle(game));
}

void	init_weapon(t_game *game)
{
	game->wd.width = game->gun.width;
	game->wd.height = game->gun.height;
	game->wd.line_len = game->gun.img.line_len;
	game->wd.bpp = game->gun.img.bpp;
	game->wd.addr = game->gun.img.addr;
	game->wd.weapon_x = 0;
	game->wd.weapon_y = HEIGHT - game->gun.height;
}

static void	draw_weapon_static(t_game *game, int i, int j)
{
	int	screen_x;
	int	screen_y;

	screen_x = game->wd.weapon_x + i;
	screen_y = game->wd.weapon_y + j;
	game->wd.src_i = i;
	game->wd.src_j = j;
	draw_weapon_pixel(game, screen_x, screen_y);
}

void	render_weapon(t_game *game)
{
	int				i;
	int				j;
	double			angle;

	init_weapon(game);
	j = 0;
	angle = calculate_weapon_animation(game);
	while (j < game->wd.height)
	{
		i = 0;
		while (i < game->wd.width)
		{
			if (game->weapon_anim)
				draw_weapon_animating(game, i, j, angle);
			else
				draw_weapon_static(game, i, j);
			i++;
		}
		j++;
	}
}
