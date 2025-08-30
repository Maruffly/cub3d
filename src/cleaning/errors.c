/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:21:30 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/23 11:44:12 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	error_msg(const char *msg)
{
	printf("Error:\n");
	printf("%s\n", msg);
	return (1);
}

int	exit_cub3d(t_game *game)
{
	exit_and_free(game);
	return (0);
}

// void	free_config_before_mlx(t_game *game)
// {
// 	if (game->tex_paths.north)
// 		free(game->tex_paths.north);
// 	if (game->tex_paths.south)
// 		free(game->tex_paths.south);
// 	if (game->tex_paths.east)
// 		free(game->tex_paths.east);
// 	if (game->tex_paths.west)
// 		free(game->tex_paths.west);
// 	if (game->tex_paths.door)
// 		free(game->tex_paths.door);
// 	if (game->map.file)
// 		free_split(game->map.file);
// 	if (game->map.map)
// 		free_split(game->map.map);
// }

void	exit_parse_error(t_game *game)
{
	if (game->tex_paths.north)
		free(game->tex_paths.north);
	if (game->tex_paths.south)
		free(game->tex_paths.south);
	if (game->tex_paths.east)
		free(game->tex_paths.east);
	if (game->tex_paths.west)
		free(game->tex_paths.west);
	if (game->tex_paths.door)
		free(game->tex_paths.door);
	if (game->map.file)
		free_split(game->map.file);
	if (game->map.map)
		free_split(game->map.map);
	exit(1);
}

void	free_parsing_data(t_game *game)
{
	if (game->map.file)
		free_split(game->map.file);
	if (game->tex_paths.north)
		free(game->tex_paths.north);
	if (game->tex_paths.south)
		free(game->tex_paths.south);
	if (game->tex_paths.east)
		free(game->tex_paths.east);
	if (game->tex_paths.west)
		free(game->tex_paths.west);
	if (game->map.map)
		free_split(game->map.map);
}

void	exit_and_free(t_game *game)
{
	if (!game)
		exit(1);
	if (game->doors.doors)
		free(game->doors.doors);
	if (game->map.file)
		free_split(game->map.file);
	if (game->map.map)
		free_split(game->map.map);
	game->map.file = NULL;
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->enemies)
		free_enemies(game);
	destroy_loaded_textures(game);
	free_tex_paths(game);
	free_main_image(game);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		mlx_loop_end(game->mlx);
		free(game->mlx);
	}
	exit(1);
}
