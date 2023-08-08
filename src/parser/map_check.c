/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 11:35:42 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/08 22:19:29 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_contents(t_data *data)
{
	data->no = get_content(data, "NO");
	if
	data->so = get_content(data, "SO");
	data->ea = get_content(data, "EA");
	data->we = get_content(data, "WE");
}

void	get_raw_map(t_data *data, char *src)
{
	int	fd;
	int	i;

	fd = open(src, O_RDONLY);
	if (fd < 0)
		ft_error(ERR_FILE, data);
	i = 0;
	data->raw_map[i] = get_next_line(fd);
	while (data->raw_map[i])
	{
		i++;
		data->raw_map[i] = get_next_line(fd);
	}	
	data->raw_map[i] = 0;
}

void	map_check(t_data *data, char *src)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open(src, O_RDONLY);
	if (fd < 0)
		ft_error(ERR_FILE, data);
	i = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		free (tmp);
		tmp = get_next_line(fd);
		i++;
	}
	close(fd);
	data->raw_map = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->raw_map)
		ft_error(ERR_MALLOC, data);
	get_raw_map(data, src);
	check_contents(game, raw_map);
}
