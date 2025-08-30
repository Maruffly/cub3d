/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:17:09 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/19 14:18:21 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_pixel_color(t_game *game, t_img *img, int x, int y)
{
	int	color;
	int	tex_index;

	tex_index = game->tex_paths.cardinal;
	color = get_texture_pixel(&game->textures[tex_index], x, y);
	if (color <= 0)
	{
		if (y < game->win_height / 2)
			color = game->color.sky;
		else
			color = game->color.floor;
	}
	draw_pixel(img, x, y, color);
}

void	extract_and_blend(unsigned int *color_ptr)
{
	unsigned int	current_color;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	current_color = *color_ptr;
	r = (current_color >> 16) & 0xFF;
	g = (current_color >> 8) & 0xFF;
	b = current_color & 0xFF;
	if (r + 100 > 255)
		r = 255;
	else
		r += 100;
	if (g > 30)
		g -= 30;
	else
		g = 0;
	if (b > 30)
		b -= 30;
	else
		b = 0;
	*color_ptr = (r << 16) | (g << 8) | b;
}

void	render_red_effect(t_game *game)
{
	int				x;
	int				y;
	int				pixel_idx;
	unsigned int	*color_ptr;

	y = 0;
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			pixel_idx = y * game->img.line_len + x * (game->img.bpp / 8);
			color_ptr = (unsigned int *)(game->img.addr + pixel_idx);
			extract_and_blend(color_ptr);
			x++;
		}
		y++;
	}
}
