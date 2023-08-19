/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:32:19 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/16 12:50:16 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_top_wall(t_game *game, int flag_start, int flag_end)
{
	int		i;
	char	ocr;

	i = -1;
	while (game->data->map[0][++i])
	{
		ocr = get_top(game->data->map, i);
		if (flag_start == 1 && flag_end == 0)
		{
			if (ocr != '1' && ocr != ' ')
				data_error(ERR_WALL, game);
			if (ocr == '1')
				flag_start = 0;
		}
		else if (flag_start == 0 && flag_end == 0)
		{
			if (ocr != '1' && ocr != ' ')
				data_error(ERR_WALL, game);
			if (ocr == ' ')
				flag_end = 1;
		}
		else if (flag_start == 0 && flag_end == 1)
			if (ocr != ' ')
				data_error(ERR_WALL, game);
	}
}

void	check_bottom_wall(t_game *game)
{
	int		i;
	char	ocr;

	i = -1;
	while (game->data->map[++i])
	{
		ocr = get_bottom(game->data->map, i);
		if (ocr != '1' && ocr != ' ')
			data_error(ERR_WALL, game);
	}
}

void	check_left_wall(t_game *game)
{
	int		i;
	char	ocr;

	i = -1;
	while (game->data->map[++i])
	{
		ocr = get_left(game->data->map[i]);
		if (ocr != '1')
			data_error(ERR_WALL, game);
	}
}

void	check_right_wall(t_game *game)
{
	int		i;
	char	ocr;

	i = -1;
	while (game->data->map[++i])
	{
		ocr = get_right(game->data->map[i]);
		if (ocr != '1')
			data_error(ERR_WALL, game);
	}
}

void	check_map(t_game *game)
{
	int	i;

	i = 0;
	if (char_counter(game->data->map, 'N'))
		i++;
	if (char_counter(game->data->map, 'S'))
		i++;
	if (char_counter(game->data->map, 'E'))
		i++;
	if (char_counter(game->data->map, 'W'))
		i++;
	if (i != 1)
		data_error(ERR_CHAR, game);
	check_top_wall(game, 1, 0);
	check_bottom_wall(game);
	check_left_wall(game);
	check_right_wall(game);
	get_player(game);
}
