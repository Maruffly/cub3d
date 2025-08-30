/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:40:00 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/23 11:43:44 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_cub_file(char *filename)
{
	if (is_dir(filename) == true)
		return (error_msg("Provided file is a directory"));
	if (!parse_extension(filename))
		return (error_msg("Invalid file format, .cub file needed"));
	return (0);
}

// int	check_xpm_paths(t_tex_paths *tex)
// {
// 	if (!is_xpm_file(tex->north))
// 		return (error_msg("Texture NO is not a valid .xpm file"));
// 	if (!is_xpm_file(tex->south))
// 		return (error_msg("Texture SO is not a valid .xpm file"));
// 	if (!is_xpm_file(tex->west))
// 		return (error_msg("Texture WE is not a valid .xpm file"));
// 	if (!is_xpm_file(tex->east))
// 		return (error_msg("Texture EA is not a valid .xpm file"));
// 	return (0);
// }

// int	parse_arg(t_game *game, char **av)
// {
// 	if (parse_cub_file(av[1]) != 0)
// 		exit_parse_error(game);
// 	game->map.path = av[1];
// 	if (load_map(game) != 0)
// 		exit_parse_error(game);
// 	if (parse_config(game) != 0)
// 		exit_parse_error(game);
// 	if (check_xpm_paths(&game->tex_paths) != 0)
// 		exit_parse_error(game);
// 	if (extract_map_only(game) != 0)
// 		exit_parse_error(game);
// 	if (validate_map(game) != 0)
// 		exit_parse_error(game);
// 	return (0);
// }

int	is_valid_xpm(const char *path)
{
	int		len;
	int		fd;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

void	free_paths(t_tex_paths *paths)
{
	if (paths->north)
		free(paths->north);
	if (paths->south)
		free(paths->south);
	if (paths->east)
		free(paths->east);
	if (paths->west)
		free(paths->west);
	paths->north = NULL;
	paths->south = NULL;
	paths->east = NULL;
	paths->west = NULL;
}

int	check_xpm_paths(t_game *game)
{
	if (!is_valid_xpm("assets/doors.xpm")
		|| !is_valid_xpm("assets/omar.xpm")
		|| !is_valid_xpm("assets/gun.xpm")
		|| !is_valid_xpm("assets/fred.xpm"))
	{
		error_msg("Missing or invalid .xpm texture file in assets");
		free_paths(&game->tex_paths);
		free_split(game->map.file);
		free_paths(&game->tex_paths);
		free_split(game->map.file);
		exit(1);
	}
	return (0);
}

int	parse_arg(t_game *game, char **av)
{
	if (parse_cub_file(av[1]) != 0)
		exit_parse_error(game);
	game->map.path = av[1];
	if (load_map(game) != 0)
		exit_parse_error(game);
	if (parse_config(game) != 0)
		exit_parse_error(game);
	if (check_xpm_paths(game) != 0)
		exit_parse_error(game);
	if (extract_map_only(game) != 0)
		exit_parse_error(game);
	if (validate_map(game) != 0)
		exit_parse_error(game);
	return (0);
}
