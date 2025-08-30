/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:18:07 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/22 18:36:10 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	update_ray_step(t_ray *ray)
{
	if (ray->side_x < ray->side_y)
	{
		ray->side_x += ray->delta_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_y += ray->delta_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

static int	ray_hit_boundary_or_wall(t_game *game, t_ray *ray)
{
	int	cur_cell;

	if (ray->map_x < 0 || ray->map_x >= game->map.map_width
		|| ray->map_y < 0 || ray->map_y >= game->map.map_height)
		return (1);
	cur_cell = game->map.map[ray->map_y][ray->map_x];
	if (cur_cell == WALL || cur_cell == DOOR)
	{
		ray->is_door = (cur_cell == DOOR);
		return (1);
	}
	return (0);
}

void	dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		update_ray_step(ray);
		hit = ray_hit_boundary_or_wall(game, ray);
	}
}
