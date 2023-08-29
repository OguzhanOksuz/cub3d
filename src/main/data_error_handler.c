/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_error_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:20:05 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/29 17:35:04 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	char_arr_free(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i] != 0)
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr);
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->file !=  0)
			char_arr_free(data->file);
		if (data->map != 0)
			char_arr_free(data->map);
		if (data->tmp != 0)
			free(data->tmp);
		if (data->no != 0)
			free(data->no);
		if (data->so != 0)
			free(data->so);
		if (data->ea != 0)
			free(data->ea);
		if (data->we != 0)
			free(data->we);
		if (data->f != 0)
			free(data->f);
		if (data->c != 0)
			free(data->c);
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
	else if (err == ERR_EXIT)
		write(1, "Pressed esc\n", 12);
	free_data(game->data);
	free(game);
	//system("leaks cub3d");
	exit(1);
}
