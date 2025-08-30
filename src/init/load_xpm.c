/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:00:39 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/23 12:14:27 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_texture(t_game *game, char *path, t_texture *tex)
{
	if (!is_valid_xpm(path))
		exit_parse_error(game);
	tex->img.img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img.img)
	{
		printf("Error:\n");
		printf("Unable to load %s\n", path);
		exit_parse_error(game);
	}
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	if (!tex->img.addr)
	{
		printf("Error:\n");
		printf("Failed to get image address for %s\n", path);
		exit_parse_error(game);
	}
}

void	set_texture(t_game *game)
{
	if (game->tex_paths.north)
		load_texture(game, game->tex_paths.north, &game->textures[0]);
	if (game->tex_paths.south)
		load_texture(game, game->tex_paths.south, &game->textures[1]);
	if (game->tex_paths.west)
		load_texture(game, game->tex_paths.west, &game->textures[2]);
	if (game->tex_paths.east)
		load_texture(game, game->tex_paths.east, &game->textures[3]);
	load_texture(game, "assets/doors.xpm", &game->textures[4]);
	load_texture(game, "assets/omar.xpm", &game->omar);
	load_texture(game, "assets/gun.xpm", &game->gun);
	load_texture(game, "assets/fred.xpm", &game->player_face);
}
