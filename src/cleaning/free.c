/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorislaine <jorislaine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:50:56 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/20 00:53:47 by jorislaine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	free_split(char **split)
{
	int	i;

	if (!split)
		return (1);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (1);
}

void	destroy_loaded_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (game->textures[i].img.img)
			mlx_destroy_image(game->mlx, game->textures[i].img.img);
		i++;
	}
	if (game->omar.img.img)
		mlx_destroy_image(game->mlx, game->omar.img.img);
	if (game->gun.img.img)
		mlx_destroy_image(game->mlx, game->gun.img.img);
	if (game->player_face.img.img)
		mlx_destroy_image(game->mlx, game->player_face.img.img);
}

void	free_enemies(t_game *game)
{
	int	i;

	if (!game->enemies)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].texture.img.img)
			mlx_destroy_image(game->mlx, game->enemies[i].texture.img.img);
		i++;
	}
	free(game->enemies);
	game->enemies = NULL;
}

void	free_tex_paths(t_game *game)
{
	if (game->tex_paths.north)
		free(game->tex_paths.north);
	if (game->tex_paths.south)
		free(game->tex_paths.south);
	if (game->tex_paths.west)
		free(game->tex_paths.west);
	if (game->tex_paths.east)
		free(game->tex_paths.east);
	game->tex_paths.north = NULL;
	game->tex_paths.south = NULL;
	game->tex_paths.west = NULL;
	game->tex_paths.east = NULL;
}

void	free_main_image(t_game *game)
{
	if (game->mlx && game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = NULL;
	game->img.addr = NULL;
}
