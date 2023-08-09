/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:48:01 by mkaraden          #+#    #+#             */
/*   Updated: 2023/08/09 22:25:30 by ooksuz           ###   ########.fr       */
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

void	trim_file(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->data->file[i])
		i++;
	i--;
	while (game->data->file[i])
	{
		j = 0;
		while (game->data->file[i][j] == ' ' ||
			game->data->file[i][j] == '\n')
			j++;
		if (j == ft_strlen(game->data->file[i]))
		{
			free(game->data->file[i]);
			game->data->file[i] = 0;
		}
		else
			break ;
		i--;
	}
}

void	get_map(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (game->data->file[i])
		i++;
	j = i - 1;
	while (is_mapline(game->data->file[j]) && j >= 0)
		j--;
	j++;
	game->data->map = (char **)malloc(sizeof(char *) * (i - j + 1));
	if (!game->data->map)
		data_error(ERR_MALLOC, game);
	k = 0;
	while (j + k < i)
	{
		game->data->map[k] = ft_strdup(game->data->file[j + k]);
		free(game->data->file[j + k]);
		game->data->file[j + k++] = 0;
	}
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
		game->data->file = NULL;
		game->data->map = "";
		printf("Kaskımı geriver 5\n");
		if (ft_strcmp(ft_strrchr(av[1], '.'), ".cub") != 0)
			data_error(ERR_EXT, game);
		printf("Kaskımı geriver \n");
		read_file(game, av[1]);
		trim_file(game);
		get_map(game);
		trim_file(game);
		get_elements(game, -1);
	}
	else
		data_error(ERR_AC, game);
	debug_data(game->data);
}
