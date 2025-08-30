/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:29:53 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/21 15:18:39 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_draw_range(t_game *game, t_enemy *enemy)
{
	int	draw_start_y;
	int	draw_end_y;

	draw_start_y = -enemy->height / 2 + game->win_height / 2;
	draw_end_y = enemy->height / 2 + game->win_height / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	if (draw_end_y >= game->win_height)
		draw_end_y = game->win_height - 1;
	enemy->draw_start_y = draw_start_y;
	enemy->draw_end_y = draw_end_y;
}

void	calculate_sprite_projection(t_game *game, t_enemy *enemy,
	int *screen_x, int *sprite_height)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;

	sprite_x = enemy->x - game->player.pos_x;
	sprite_y = enemy->y - game->player.pos_y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	transform_x = inv_det * (game->player.dir_y * sprite_x
			- game->player.dir_x * sprite_y);
	transform_y = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
	*screen_x = (int)((game->win_width / 2) * (1 + transform_x / transform_y));
	*sprite_height = abs((int)(game->win_height / transform_y));
	enemy->screen_x = *screen_x;
	enemy->height = *sprite_height;
}

static void	draw_sprite_column(t_game *game, t_enemy *enemy,
	int x, t_texture *tex)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	y = enemy->draw_start_y;
	while (y < enemy->draw_end_y)
	{
		tex_x = (int)(((x - (enemy->screen_x - enemy->height / 2)) * tex->width)
				/ enemy->height);
		tex_y = (int)(((y - enemy->draw_start_y) * tex->height)
				/ (enemy->draw_end_y - enemy->draw_start_y));
		color = get_texture_pixel(tex, tex_x, tex_y);
		if (color != (int)0xFF000000)
			draw_pixel(&game->img, x, y, color);
		y++;
	}
}

void	draw_sprite(t_game *game, t_enemy *enemy)
{
	int			x;
	t_texture	*tex;
	int			start_x;
	int			end_x;

	tex = &enemy->texture;
	start_x = enemy->screen_x - enemy->height / 2;
	end_x = enemy->screen_x + enemy->height / 2;
	x = start_x;
	while (x < end_x)
	{
		if (x > 0 && x < game->win_width)
			draw_sprite_column(game, enemy, x, tex);
		x++;
	}
}

void	render_enemies(t_game *game)
{
	int				i;
	int				screen_x;
	int				sprite_height;
	t_enemy			*enemy;

	sort_enemies_by_distance(game);
	i = 0;
	while (i < game->enemy_count)
	{
		enemy = &game->enemies[i];
		if (enemy->is_alive)
		{
			move_enemy_towards_player(game, enemy);
			if (!game->enemies->visible)
			{
				i++;
				continue ;
			}
			calculate_sprite_projection(game, enemy, &screen_x, &sprite_height);
			set_draw_range(game, enemy);
			draw_sprite(game, enemy);
		}
		i++;
	}
}
