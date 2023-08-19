/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:05:35 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/14 15:49:49 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	char_counter(char **map, char ch)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == ch)
				count++;
	}
	return (count);
}

void	trim_nl(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->data->map[++i])
	{
		j = 0;
		while (game->data->map[i][j])
			j++;
		if (j > 0)
			if (game->data->map[i][j - 1] == '\n')
				game->data->map[i][j - 1] = 0;
	}
}

void	square_map(t_game *game)
{
	char	*line;
	int		i;
	int		j;

	i = -1;
	while (game->data->map[++i])
	{
		j = 0;
		while (game->data->map[i][j])
			j++;
		if (j < game->data->map_width)
		{
			line = (char *)malloc(sizeof(char) * (game->data->map_width + 1));
			if (!line)
				data_error(ERR_MALLOC, game);
			j = -1;
			while (game->data->map[i][++j])
				line[j] = game->data->map[i][j];
			while (j < game->data->map_width)
				line[j++] = ' ';
			line[game->data->map_width] = 0;
			free(game->data->map[i]);
			game->data->map[i] = line;
		}
	}
}

void	format_map(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->data->map[++i])
	{
		j = -1;
		while (game->data->map[i][++j])
			if (game->data->map[i][j] == ' ')
				game->data->map[i][j] = '1';
	}
}
