/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:35:30 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/12 22:18:13 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi(char	*num)
{
	int	i;
	int	rt;

	rt = 0;
	i = 0;
	while (num[i])
	{
		rt = (rt * 10) + num[i] - '0';
		i++;
	}
	return (rt);
}

void	check_elements(t_game *game, int fd)
{
	if (ft_strcmp(ft_strrchr(game->data->no, '.'), ".xpm"))
		data_error(ERR_EXT, game);
	if (ft_strcmp(ft_strrchr(game->data->so, '.'), ".xpm"))
		data_error(ERR_EXT, game);
	if (ft_strcmp(ft_strrchr(game->data->ea, '.'), ".xpm"))
		data_error(ERR_EXT, game);
	if (ft_strcmp(ft_strrchr(game->data->we, '.'), ".xpm"))
		data_error(ERR_EXT, game);
	fd = open(game->data->no, O_RDONLY);
	close(fd);
	if (fd < 0)
		data_error(ERR_PATH, game);
	fd = open(game->data->so, O_RDONLY);
	close(fd);
	if (fd < 0)
		data_error(ERR_PATH, game);
	fd = open(game->data->ea, O_RDONLY);
	close(fd);
	if (fd < 0)
		data_error(ERR_PATH, game);
	fd = open(game->data->we, O_RDONLY);
	close(fd);
	if (fd < 0)
		data_error(ERR_PATH, game);
}

void	arr_free(int err, t_game *game, char **arr)
{
	int	i;

	if (arr)
	{
		i = -1;
		while (arr[++i])
			free(arr[i]);
	}
	if (err != 2147483647)
		data_error(err, game);
}

int	check_color(t_game *game, char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
		i++;
	if (i-- != 3)
		arr_free(ERR_ELEM, game, arr);
	while (i >= 0 && arr[i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (arr[i][j] > '9' || arr[i][j] < '0' || j > 2)
				arr_free(ERR_ELEM, game, arr);
		}
		if (ft_atoi(arr[i]) > 255)
			arr_free(ERR_ELEM, game, arr);
		i--;
	}
	return (ft_atoi(arr[0]) << 16 | ft_atoi(arr[1]) << 8 | ft_atoi(arr[2]));
}

void	lexer(t_game *game)
{
	char	**arr;

	check_elements(game, -1);
	arr = ft_split(game->data->f, ',', game);
	if (!arr)
		data_error(ERR_MALLOC, game);
	game->data->floor = check_color(game, arr);
	arr_free(2147483647, game, arr);
	arr = ft_split(game->data->c, ',', game);
	if (!arr)
		data_error(ERR_MALLOC, game);
	game->data->ceiling = check_color(game, arr);
	arr_free(2147483647, game, arr);
}
