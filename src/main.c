/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:09:48 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/22 13:21:55 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (error_msg("Usage: ./cub3d <path/to/map.cub>"));
	init_game(&game);
	if (parse_arg(&game, av))
		return (1);
	init_mlx(&game);
	init_enemies(&game);
	set_texture(&game);
	init_doors(&game);
	display(&game);
	key_events_handler(&game);
	mlx_loop_hook(game.mlx, display, &game);
	mlx_loop(game.mlx);
}
