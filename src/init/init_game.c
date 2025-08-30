/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:59:27 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/23 12:48:46 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_map(t_map *map)
{
	map->fd = 0;
	map->player = 0;
	map->path = NULL;
	map->file = NULL;
	map->map_width = 0;
	map->map_height = 0;
	map->line_count = 0;
	map->map = NULL;
}

void	init_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
}

void	init_player(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
	player->dir = 0;
	player->moved = false;
}

void	init_minimap(t_minimap *mini)
{
	mini->line_length = 0;
	mini->delta_x = 0;
	mini->delta_y = 0;
}

void	init_game(t_game *game)
{
	game->win = NULL;
	game->mlx = NULL;
	game->win_width = WIDTH;
	game->win_height = HEIGHT;
	if (IS_BONUS)
		game->mouse_enabled = 1;
	else
		game->mouse_enabled = 0;
	game->weapon_anim = false;
	game->weapon_anim_frames = 20;
	game->weapon_anim_counter = 0;
	game->proximity_threshold = 2.0;
	game->screen_red = false;
	game->attack_counter = 0;
	init_player(&game->player);
	init_texture(&game->tex_paths);
	init_img(&game->img);
	init_map(&game->map);
	init_minimap(&game->mini);
}
