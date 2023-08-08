/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:48:01 by mkaraden          #+#    #+#             */
/*   Updated: 2023/08/09 00:03:08 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_file(t_game *game, char *src)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open(src, O_RDONLY);
	if (fd < 0)
		data_error(ERR_PATH, game);
	i = 0;
	tmp = get_next_line(fd);
	while (tmp && ++i)
	{
		free (tmp);
		tmp = get_next_line(fd);
	}
	printf("line = %d\n", i);
	close (fd);
	game->data->file = (char **)malloc(sizeof(char *) * (i + 1));
	if (!game->data->file)
		data_error(ERR_MALLOC, game);
	fd = open(src, O_RDONLY);
	i = 0;
	game->data->file[0] = get_next_line(fd);
	while (game->data->file[i])
		game->data->file[++i] = get_next_line(fd);
	game->data->file[i] = 0;
}

void	parse_cub(t_game *game, int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		data = (t_data *)malloc(sizeof(data));
		if (!data)
			data_error(ERR_MALLOC, game);
		game->data = data;
		if (ft_strcmp(ft_strrchr(av[1], '.') + 1, "cub") != 0)
			data_error(ERR_EXT, game);
		read_file(game, av[1]);
		check_elements(game);
	}
	else
		data_error(ERR_AC, game);
}
