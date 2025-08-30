/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:52:08 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/19 14:24:15 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_minimap_bounds(t_game *game, double x, double y)
{
	return (x < 0 || x >= game->mini.minimap_width
		|| y < 0 || y >= game->mini.minimap_height);
}

int	check_wall_collision(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)((x - MINIMAP_X) / CELL_SIZE);
	map_y = (int)((y - MINIMAP_Y) / CELL_SIZE);
	if (map_x < 0 || map_x >= game->map.map_width
		|| map_y < 0 || map_y >= game->map.map_height
		|| game->map.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	minimap_dimensions(t_game *game)
{
	game->mini.minimap_width = game->map.map_width * CELL_SIZE;
	game->mini.minimap_height = game->map.map_height * CELL_SIZE;
	if (game->mini.minimap_width < MIN_MINIMAP_SIZE)
		game->mini.minimap_width = MIN_MINIMAP_SIZE;
	if (game->mini.minimap_height < MIN_MINIMAP_SIZE)
		game->mini.minimap_height = MIN_MINIMAP_SIZE;
	if (game->mini.minimap_width > MAX_MINIMAP_WIDTH)
		game->mini.minimap_width = MAX_MINIMAP_WIDTH;
	if (game->mini.minimap_height > MAX_MINIMAP_HEIGHT)
		game->mini.minimap_height = MAX_MINIMAP_HEIGHT;
}

int	check_ray_hit(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / CELL_SIZE);
	map_y = (int)(y / CELL_SIZE);
	if (map_x < 0 || map_x >= game->map.map_width
		|| map_y < 0 || map_y >= game->map.map_height)
		return (1);
	if (game->map.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	initialize_ray(t_game *game, int i, int ray_count, t_ray *ray)
{
	double	camera_x;
	double	length;

	camera_x = 2.0 * i / (double)(ray_count - 1) - 1.0;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	length = sqrt(ray->dir_x * ray->dir_x + ray->dir_y * ray->dir_y);
	ray->dir_x /= length;
	ray->dir_y /= length;
	if (i % 5 == 0)
		ray->color = 0xFFFF8800;
	else
		ray->color = 0xFFDD8800;
}
