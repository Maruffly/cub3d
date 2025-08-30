/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:40:44 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/23 11:33:58 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_pixel(t_img *img, int x, int y, int color)
{
	int		pixel_idx;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	if (!img || !img->addr)
		return ;
	pixel_idx = y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)(img->addr + pixel_idx) = color;
}

static void	render_assets(t_game *game)
{
	if (IS_BONUS)
	{
		render_enemies(game);
		render_minimap(game);
		render_weapon(game);
	}
}

void	render_frame(t_game *game)
{
	t_img	*image;
	int		x;
	int		y;

	y = 0;
	image = &game->img;
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			if (y < game->win_height / 2)
				draw_pixel(&game->img, x, y, game->color.sky);
			else
				draw_pixel(&game->img, x, y, game->color.floor);
			x++;
		}
		y++;
	}
	raycaster(game);
	render_assets(game);
	if (game->screen_red)
		render_red_effect(game);
	mlx_put_image_to_window(game->mlx, game->win, image->img, 0, 0);
}

void	update_enemy_visibility(t_game *game)
{
	int		i;
	t_enemy	*enemy;

	i = 0;
	while (i < game->enemy_count)
	{
		enemy = &game->enemies[i];
		if (enemy->is_alive)
			game->enemies->visible = is_enemy_visible(game, enemy);
		else
			game->enemies->visible = false;
		i++;
	}
}

int	display(t_game *game)
{
	bool	has_moved;

	has_moved = move(game);
	game->player.moved = has_moved;
	if (IS_BONUS)
	{
		update_enemy_visibility(game);
		check_enemy_proximity(game);
	}
	if (game->attack_counter == 5)
	{
		write(1, BOLD RED"YOU DIED!\n"RESET, 18);
		exit_and_free(game);
	}
	render_frame(game);
	return (0);
}
