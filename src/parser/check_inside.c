/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:50:48 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/16 20:05:22 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_side(t_game *game, int i, int j)
{
	if (i > 0)
		if (game->data->map[i - 1][j] != ' '
			&& game->data->map[i - 1][j] != '1')
			data_error(ERR_WALL, game);
	if (game->data->map[i + 1] != 0)
		if (game->data->map[i + 1][j] != ' '
			&& game->data->map[i + 1][j] != '1')
			data_error(ERR_WALL, game);
	if (j > 0)
		if (game->data->map[i][j - 1] != ' '
			&& game->data->map[i][j - 1] != '1')
			data_error(ERR_WALL, game);
	if (game->data->map[i][j + 1] != 0)
		if (game->data->map[i][j + 1] != ' '
			&& game->data->map[i][j + 1] != '1')
			data_error(ERR_WALL, game);
}

void	check_inside(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->data->map[++i])
	{
		j = -1;
		while (game->data->map[i][++j])
		{
			if (game->data->map[i][j] == ' ')
				check_side(game, i, j);
		}
	}
}
