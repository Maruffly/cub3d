/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:55:18 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/22 12:32:13 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_player_face(t_game *game, int x, int y)
{
	int				i;
	int				j;
	int				face_size;
	unsigned int	color;
	int				src_idx;

	face_size = 85;
	i = 0;
	while (i < face_size)
	{
		j = 0;
		while (j < face_size)
		{
			src_idx = (j * game->player_face.height / face_size)
				* game->player_face.img.line_len
				+ (i * game->player_face.width / face_size)
				* (game->player_face.img.bpp / 8);
			color = *(unsigned int *)(game->player_face.img.addr + src_idx);
			if (color != 0xFF000000)
				draw_minimap_pixel(game, x - face_size / 2 + i,
					y - face_size / 2 + j, color);
			j++;
		}
		i++;
	}
}

void	cast_ray(t_game *game, double start_x, double start_y, t_ray ray)
{
	double	x;
	double	y;
	int		step;
	double	step_size;
	int		max_steps;

	x = start_x;
	y = start_y;
	step = 0;
	step_size = 0.3;
	max_steps = 100;
	while (step < max_steps)
	{
		if (check_wall_collision(game, x, y))
			break ;
		draw_minimap_pixel(game, (int)(x - MINIMAP_X), \
		(int)(y - MINIMAP_Y), ray.color);
		x += ray.dir_x * step_size * CELL_SIZE;
		y += ray.dir_y * step_size * CELL_SIZE;
		step++;
	}
}

void	draw_ray_beam(t_game *game, int player_x, int player_y)
{
	int		i;
	int		ray_count;
	double	center_x;
	double	center_y;

	center_x = MINIMAP_X + player_x;
	center_y = MINIMAP_Y + player_y;
	ray_count = 40;
	i = 0;
	while (i < ray_count)
	{
		initialize_ray(game, i, ray_count, &game->ray);
		cast_ray(game, center_x, center_y, game->ray);
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int	player_screen_x;
	int	player_screen_y;

	player_screen_x = (int)(game->player.pos_x * CELL_SIZE);
	player_screen_y = (int)(game->player.pos_y * CELL_SIZE);
	minimap_dimensions(game);
	render_minimap_background(game);
	render_minimap_tiles(game);
	draw_ray_beam(game, player_screen_x, player_screen_y);
	draw_player_face(game, player_screen_x, player_screen_y);
}
