/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:03:15 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/09 14:50:24 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	word_counter(char *line)
{
	int	i;
	int	count;
	int	flag;

	count = 0;
	i = -1;
	flag = 0;
	while (line[++i])
	{
		if (line[i] == ' ')
			flag = 1;
		else if (flag == 1 && line[i] != '\n')
		{
			count++;
			flag = 0;
		}
	}
	if (count == 2 || count == 0)
		return (1);
	return (0);
}

void	get_elements(t_game *game)
{
	int	i;

	i = -1;
	while (game->data->file[++i])
	{
		if (!(word_counter(game->data->file[i])))
			data_error(ERR_ELEM, game);
		game->data->tmp = get_word(game->data->file[i], 1);
		if (ft_strcmp(game->data->tmp, "NO") == 0)
			game->data->no = ft_strdup(game->data->tmp);
		else if (ft_strcmp(game->data->tmp, "SO") == 0)
			game->data->so = ft_strdup(game->data->tmp);
		else if (ft_strcmp(game->data->tmp, "EA") == 0)
			game->data->ea = ft_strdup(game->data->tmp);
		else if (ft_strcmp(game->data->tmp, "WE") == 0)
			game->data->we = ft_strdup(game->data->tmp);
		else if (ft_strcmp(game->data->tmp, "F") == 0)
			game->data->f = ft_strdup(game->data->tmp);
		else if (ft_strcmp(game->data->tmp, "C") == 0)
			game->data->c = ft_strdup(game->data->tmp);
		else
			data_error(ERR_ELEM, game);
	}
}
