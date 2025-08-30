/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:05:36 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/19 12:18:24 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_minimap_pixel(t_game *game, int x, int y, int color)
{
	int	pixel_idx;
	int	screen_x;
	int	screen_y;

	screen_x = MINIMAP_X + x;
	screen_y = MINIMAP_Y + y;
	if (screen_x < MINIMAP_X || screen_x >= MINIMAP_X + \
		game->mini.minimap_width || screen_y < MINIMAP_Y
		|| screen_y >= MINIMAP_Y + game->mini.minimap_height)
		return ;
	if (screen_x < 0 || screen_x >= WIDTH || screen_y < 0 || screen_y >= HEIGHT)
		return ;
	pixel_idx = screen_y * game->img.line_len + screen_x * (game->img.bpp / 8);
	*(unsigned int *)(game->img.addr + pixel_idx) = color;
}

void	draw_minimap_rectangle(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	size = CELL_SIZE;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			draw_minimap_pixel(game, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	render_minimap_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->mini.minimap_height)
	{
		x = 0;
		while (x < game->mini.minimap_width)
		{
			draw_minimap_pixel(game, x, y, 0x80000000);
			x++;
		}
		y++;
	}
}

void	render_tile(t_game *game, int map_x, int map_y)
{
	int	screen_x;
	int	screen_y;
	int	color;

	screen_x = map_x * CELL_SIZE;
	screen_y = map_y * CELL_SIZE;
	if (screen_x >= 0 && screen_x < game->mini.minimap_width - CELL_SIZE
		&& screen_y >= 0 && screen_y < game->mini.minimap_height - CELL_SIZE)
	{
		if (game->map.map[map_y][map_x] == '1')
			color = 0xFFFFFFFF;
		else
			color = 0xFF333333;
		draw_minimap_rectangle(game, screen_x, screen_y, color);
	}
}

void	render_minimap_tiles(t_game *game)
{
	int	map_y;
	int	map_x;
	int	line_length;

	map_y = 0;
	map_x = 0;
	while (map_y < game->map.map_height)
	{
		map_x = 0;
		line_length = ft_strlen(game->map.map[map_y]);
		while (map_x < line_length)
		{
			render_tile(game, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
}
