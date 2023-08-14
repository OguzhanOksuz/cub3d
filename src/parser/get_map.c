/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:26 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/14 17:50:11 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	get_top(char **map, int column)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (map[i][column] != ' ')
			return (map[i][column]);
	}
	return (' ');
}

char	get_bottom(char **map, int column)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	while (--i >= 0)
	{
		if (map[i][column] != ' ')
			return (map[i][column]);
	}
	return (' ');
}

char	get_left(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] != ' ')
			return (line[i]);
	return (' ');
}

char	get_right(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	while (--i >= 0)
		if (line[i] != ' ')
			return (line[i]);
	return (' ');
}

void	get_map_val(t_game *game)
{
	int	i;
	int	j;
	int	tmp;

	tmp = 0;
	i = -1;
	while (game->data->map[++i])
	{
		j = 0;
		while (game->data->map[i][j])
			j++;
		if (j > tmp)
			tmp = j;
	}
	game->data->map_height = i;
	game->data->map_width = tmp;
}
