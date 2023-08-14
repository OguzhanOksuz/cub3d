/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:58:23 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/14 18:06:34 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_dir(char ch)
{
	if (ch == 'N')
		return (1);
	if (ch == 'S')
		return (1);
	if (ch == 'E')
		return (1);
	if (ch == 'W')
		return (1);
	return (0);
}

void	get_player(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->data->map[++i])
	{
		j = -1;
		while (game->data->map[i][++j])
		{
			if (game->data->map[i][j] == 'N')
				game->data->dir = NORTH;
			if (game->data->map[i][j] == 'S')
				game->data->dir = SOUTH;
			if (game->data->map[i][j] == 'E')
				game->data->dir = EAST;
			if (game->data->map[i][j] == 'W')
				game->data->dir = WEST;
			if (is_dir(game->data->map[i][j]))
			{
				game->data->x = i;
				game->data->y = j;
				return ;
			}
		}
	}
}
