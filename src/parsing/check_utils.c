/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:48:45 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/23 12:49:26 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_valid_map_char(char c)
{
	if (IS_BONUS && (c == '0' || c == '1' || c == 'N'
			|| c == 'S' || c == 'E' || c == 'W' || c == ' '
			|| c == 'D' || c == 'O' || c == 'X'))
		return (1);
	if (!IS_BONUS && (c == '0' || c == '1' || c == 'N'
			|| c == 'S' || c == 'E' || c == 'W' || c == ' '))
		return (1);
	else
		return (0);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_doors(char c)
{
	return (c == DOOR || c == DOOR_OPEN);
}

int	count_newlines_in_buffer(char *buffer, ssize_t bytes)
{
	ssize_t	i;
	int		count;

	i = 0;
	count = 0;
	while (i < bytes)
	{
		if (buffer[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
