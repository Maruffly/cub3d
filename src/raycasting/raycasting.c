/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:16:52 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/22 11:07:51 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_raycasting(int x, t_ray *ray, t_player *player)
{
	init_ray(ray);
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}

void	calculate_step_side(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_y;
	}
}

void	calculate_wall_distance(t_ray *ray, t_player *player, t_game *game)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x) / 2)
			/ ray->dir_x;
	else
		ray->wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y) / 2)
			/ ray->dir_y;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->line_height = (int)(game->win_height / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_end >= game->win_height)
		ray->draw_end = game->win_height - 1;
}

void	raycaster(t_game *game)
{
	int	x;
	int	text_idx;
	int	texture_size;

	x = 0;
	text_idx = 0;
	texture_size = 512;
	while (x < game->win_width)
	{
		set_raycasting(x, &game->ray, &game->player);
		calculate_step_side(game, &game->ray);
		dda(game, &game->ray);
		calculate_wall_distance(&game->ray, &game->player, game);
		if (game->ray.is_door)
			text_idx = 4;
		else
			text_idx = game->tex_paths.cardinal;
		update_texture(game, &game->ray, x, texture_size);
		x++;
	}
}
