/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:51:05 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/22 12:26:52 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_texture_cardinal(t_tex_paths *tex, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			tex->cardinal = WEST;
		else
			tex->cardinal = EAST;
	}
	else
	{
		if (ray->dir_y < 0)
			tex->cardinal = NORTH;
		else
			tex->cardinal = SOUTH;
	}
}

void	calculate_coordinates(t_tex_paths *tex, t_ray *ray, int texture_size)
{
	tex->x = (int)(ray->wall_x * texture_size);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
			tex->x = texture_size - tex->x - 1;
	tex->step = 1.0 * texture_size / ray->line_height;
	tex->pos = (ray->draw_start - ray->line_height / 2) * tex->step;
}

int	get_texture_pixel(t_texture *buff, int x, int y)
{
	int	pixel_idx;

	if (x < 0 || y < 0 || x >= buff->width || y >= buff->height)
		return (0);
	pixel_idx = y * buff->img.line_len + x * (buff->img.bpp / 8);
	return (*(int *)(buff->img.addr + pixel_idx));
}

int	assign_idx(t_game *game)
{
	if (game->ray.is_door)
		return (4);
	if (game->tex_paths.cardinal == NORTH)
		return (0);
	else if (game->tex_paths.cardinal == SOUTH)
		return (1);
	else if (game->tex_paths.cardinal == WEST)
		return (2);
	else if (game->tex_paths.cardinal == EAST)
		return (3);
	return (0);
}

void	update_texture(t_game *game, t_ray *ray, int x, int texture_size)
{
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

	set_texture_cardinal(&game->tex_paths, ray);
	tex_x = (int)(ray->wall_x * (double)texture_size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex_x = texture_size - tex_x - 1;
	step = 1.0 * texture_size / ray->line_height;
	tex_pos = (ray->draw_start - game->win_height \
		/ 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (texture_size - 1);
		tex_pos += step;
		draw_pixel(&game->img, x, y,
			get_texture_pixel(&game->textures[assign_idx(game)], tex_x, tex_y));
		y++;
	}
}

/* void draw_weapon(t_game *game)
{
	int i, j;
	unsigned int color;
	int screen_x, screen_y;
	int pixel_idx;
	
	int weapon_x = 0;
	int weapon_y = HEIGHT - game->gun.height;
	
	j = 0;
	while (j < game->gun.height)
	{
		i = 0;
		while (i < game->gun.width)
		{
			screen_x = weapon_x + i;
			screen_y = weapon_y + j;
			if (screen_x >= 0 && screen_x < WIDTH && screen_y >= 0 && screen_y < HEIGHT)
			{
				int src_idx = j * game->gun.img.line_len + i * (game->gun.img.bpp / 8);
				color = *(unsigned int *)(game->gun.img.addr + src_idx);
				if (color != 0xFF000000) 
				{
					pixel_idx = screen_y * game->img.line_len + screen_x * (game->img.bpp / 8);
					*(unsigned int *)(game->img.addr + pixel_idx) = color;
				}
			}
			i++;
		}
		j++;
	}
} */
