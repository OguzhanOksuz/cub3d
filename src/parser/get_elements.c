/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:03:15 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/09 19:22:31 by ooksuz           ###   ########.fr       */
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
	flag = 1;
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
	return (count);
}

char	*get_word(t_game *game, char *src, int num)
{
	int	flag;
	int	i;
	int	j;

	j = 0;
	flag = 1;
	i = -1;
	while (src[++i])
	{
		if (src[i] == ' ')
			flag = 1;
		else if (flag == 1)
		{
			num--;
			flag = 0;
		}
		if (num == 0)
		{
			while (src[i + j] && src[i + j] != ' ' && src[i + j] != '\n')
				j++;
			return (ft_substr(game, src + i, --j));
		}
	}
	return (NULL);
}

void	get_elements(t_game *game, int i)
{
	while (game->data->file[++i])
	{
		if (word_counter(game->data->file[i]) == 0)
			continue ;
		if (word_counter(game->data->file[i]) != 2)
			data_error(ERR_ELEM, game);
		game->data->tmp = get_word(game, game->data->file[i], 1);
		if (ft_strcmp(game->data->tmp, "NO") == 0)
			game->data->no = get_word(game, game->data->file[i], 2);
		else if (ft_strcmp(game->data->tmp, "SO") == 0)
			game->data->so = get_word(game, game->data->file[i], 2);
		else if (ft_strcmp(game->data->tmp, "EA") == 0)
			game->data->ea = get_word(game, game->data->file[i], 2);
		else if (ft_strcmp(game->data->tmp, "WE") == 0)
			game->data->we = get_word(game, game->data->file[i], 2);
		else if (ft_strcmp(game->data->tmp, "F") == 0)
			game->data->f = get_word(game, game->data->file[i], 2);
		else if (ft_strcmp(game->data->tmp, "C") == 0)
			game->data->c = get_word(game, game->data->file[i], 2);
		else
			data_error(ERR_ELEM, game);
		if (game->data->tmp != NULL)
			free(game->data->tmp);
	}
}
