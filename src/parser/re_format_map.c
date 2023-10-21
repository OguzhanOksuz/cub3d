/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_format_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:53:32 by ooksuz            #+#    #+#             */
/*   Updated: 2023/10/21 22:40:53 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	expend_height(t_game *game)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = (char **)malloc(sizeof(char *) * (game->data->map_width + 1));
	if (!tmp)
		data_error(ERR_MALLOC, game);
	i = -1;
	while (game->data->map[++i])
		tmp[i] = game->data->map[i];
	free(game->data->map);
	game->data->map = tmp;
	while (i < game->data->map_width)
	{
		tmp[i] = (char *)malloc(sizeof(char) * (game->data->map_width + 1));
		if (!tmp[i])
			data_error(ERR_MALLOC, game);
		j = -1;
		while (++j < game->data->map_width)
			tmp[i][j] = '1';
		tmp[i++][j] = 0;
	}
	tmp[i] = 0;
}

void	err_arr_special(t_game *game, char **tmp, int i)
{
	while (--i >= 0)
		free(tmp[i]);
	free(tmp);
	data_error(ERR_MALLOC, game);
}

void	expend_width(t_game *game)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = (char **)malloc(sizeof(char *) * (game->data->map_height + 1));
	if (!tmp)
		data_error(ERR_MALLOC, game);
	i = -1;
	while (++i < game->data->map_height)
	{
		tmp[i] = (char *)malloc(sizeof(char) * (game->data->map_height + 1));
		if (!tmp[i])
			err_arr_special(game, tmp, i);
		j = -1;
		while (game->data->map[i][++j])
			tmp[i][j] = game->data->map[i][j];
		while (j < game->data->map_height)
			tmp[i][j++] = '1';
		tmp[i][j] = 0;
		free(game->data->map[i]);
	}
	tmp[i] = 0;
	free(game->data->map);
	game->data->map = tmp;
}

void	re_format_map(t_game *game)
{
	if (game->data->map_width > game->data->map_height)
	{
		expend_height(game);
		game->data->map_height = game->data->map_width;
	}
	else if (game->data->map_height > game->data->map_width)
	{
		expend_width(game);
		game->data->map_width = game->data->map_height;
	}
}
