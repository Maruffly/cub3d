/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaine <jlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:59:40 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/23 10:58:26 by jlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray(t_ray *ray)
{
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side_x = 0;
	ray->side_y = 0;
	ray->line_height = 0;
	ray->side = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->wall_x = 0;
	ray->wall_dist = 0;
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->is_door = 0;
}

void	init_weapon_animation(t_game *game)
{
	game->weapon_anim = false;
	game->weapon_anim_frames = 20;
	game->weapon_anim_counter = 0;
}

void	init_texture(t_tex_paths *text)
{
	text->cardinal = 0;
	text->x = 0;
	text->y = 0;
	text->step = 0;
	text->pos = 0;
	text->north = NULL;
	text->south = NULL;
	text->east = NULL;
	text->west = NULL;
	text->door = NULL;
}

void	init_doors(t_game *game)
{
	count_doors(game);
	init_each_door(game);
}
