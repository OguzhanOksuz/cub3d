/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_error_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:20:05 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/08 23:33:58 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	char_arr_free(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
	}
}

void	free_data(t_data *data)
{
	if (data)
	{
		char_arr_free(data->file);
		char_arr_free(data->map);
		if (data->no)
			free(data->no);
		if (data->so)
			free(data->so);
		if (data->ea)
			free(data->ea);
		if (data->we)
			free(data->we);
		free(data);
	}
}

void	data_error(int err, t_game *game)
{
	if (err == ERR_AC)
		write(2, "Invalid argument count!\n", 24);
	else if (err == ERR_EXT)
		write(2, "Invalid extension!\n", 19);
	else if (err == ERR_ELEM)
		write(2, "Bad element!\n", 14);
	else if (err == ERR_ORDER)
		write(2, "Map order is incorrect!\n", 24);
	else if (err == ERR_CHAR)
		write(2, "Invalid character!\n", 19);
	else if (err == ERR_WALL)
		write(2, "Invalid wall!\n", 14);
	else if (err == ERR_MALLOC)
		write(2, "Malloc error!\n", 14);
	else if (err == ERR_PATH)
		write(2, "Invalid file!\n", 14);
	else if (err == ERR_READ)
		write(2, "File could not be read!\n", 24);
	free_data(game->data);
	free(game);
	exit(1);
}
