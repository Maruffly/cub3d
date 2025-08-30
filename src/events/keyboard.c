/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:09:48 by jmaruffy          #+#    #+#             */
/*   Updated: 2025/04/23 12:19:12 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	handle_movement_keys(int keysym, t_game *game)
{
	if (keysym == KEY_W)
		game->player.move_y = 1;
	if (keysym == KEY_S)
		game->player.move_y = -1;
	if (keysym == KEY_A)
		game->player.move_x = 1;
	if (keysym == KEY_D)
		game->player.move_x = -1;
	if (keysym == KEY_LEFT)
		game->player.rotate = -1;
	if (keysym == KEY_RIGHT)
		game->player.rotate = 1;
	if (keysym == KEY_ESC)
		exit_cub3d(game);
}

int	keyboard_press_handler(int keysym, t_game *game)
{
	if (keysym == KEY_E)
		interact_door(game);
	if (keysym == KEY_M && IS_BONUS)
	{
		game->mouse_enabled = !game->mouse_enabled;
		if (game->mouse_enabled)
			mlx_hook(game->win, 6, 1L << 6, mouse_move_handler, game);
		else
		{
			mlx_mouse_show(game->mlx, game->win);
			mlx_hook(game->win, 6, 0, NULL, NULL);
		}
	}
	handle_movement_keys(keysym, game);
	return (0);
}

int	keyboard_release_handler(int keysym, t_game *game)
{
	if (keysym == KEY_W && game->player.move_y == 1)
		game->player.move_y = 0;
	if (keysym == KEY_S && game->player.move_y == -1)
		game->player.move_y = 0;
	if (keysym == KEY_A && game->player.move_x == 1)
		game->player.move_x = 0;
	if (keysym == KEY_D && game->player.move_x == -1)
		game->player.move_x = 0;
	if (keysym == KEY_LEFT && game->player.rotate < 0)
		game->player.rotate = 0;
	if (keysym == KEY_RIGHT && game->player.rotate > 0)
		game->player.rotate = 0;
	if (keysym == KEY_ESC)
		exit_cub3d(game);
	return (0);
}

void	key_events_handler(t_game *game)
{
	mlx_hook(game->win, ClientMessage, NoEventMask, exit_cub3d, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, keyboard_press_handler, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask,
		keyboard_release_handler, game);
	mlx_hook(game->win, ButtonPress, ButtonPressMask,
		mouse_button_handler, game);
	if (game->mouse_enabled)
		mlx_hook(game->win, 6, 1L << 6, mouse_move_handler, game);
}
