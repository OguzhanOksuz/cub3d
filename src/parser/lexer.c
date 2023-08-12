/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 10:35:30 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/12 10:59:42 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	lexer(t_game *game)
{
	check_elements(game, -1);
}
