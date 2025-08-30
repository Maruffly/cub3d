/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:46:34 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/22 14:30:33 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	calculate_coords(int i, int j, double angle, t_weapon *wd)
{
	int		center_x;
	int		center_y;
	double	cos_angle;
	double	sin_angle;

	center_x = wd->width / 2;
	center_y = wd->height / 2;
	cos_angle = cos(angle * M_PI / 180.0);
	sin_angle = sin(angle * M_PI / 180.0);
	wd->src_i = cos_angle * (i - center_x) \
	- sin_angle * (j - center_y) + center_x;
	wd->src_j = sin_angle * (i - center_x) \
	+ cos_angle * (j - center_y) + center_y;
}

void	draw_weapon_pixel(t_game *game, int screen_x, int screen_y)
{
	unsigned int	color;
	int				pixel_idx;
	int				src_idx;

	if (screen_x < 0 || screen_x >= WIDTH || screen_y < 0 || screen_y >= HEIGHT)
		return ;
	src_idx = game->wd.src_j * game->wd.line_len + game->wd.src_i
		* (game->wd.bpp / 8);
	color = *(unsigned int *)(game->wd.addr + src_idx);
	if (color == 0xFF000000)
		return ;
	pixel_idx = screen_y * game->img.line_len + screen_x * (game->img.bpp / 8);
	*(unsigned int *)(game->img.addr + pixel_idx) = color;
}

void	draw_weapon_animating(t_game *game, int i, int j, double angle)
{
	int	screen_x;
	int	screen_y;

	screen_x = game->wd.weapon_x + i;
	screen_y = game->wd.weapon_y + j;
	calculate_coords(i, j, angle, &game->wd);
	if (game->wd.src_i >= 0 && game->wd.src_i < game->wd.width
		&& game->wd.src_j >= 0 && game->wd.src_j < game->wd.height)
		draw_weapon_pixel(game, screen_x, screen_y);
}
