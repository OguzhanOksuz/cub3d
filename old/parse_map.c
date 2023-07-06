/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:48 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/05 17:36:00 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_file(char *file)
{
	get_map(file);
	
}

char	**get_map(char *file)
{
	char	**map;
	char	*iter;
	int		fd;
	int		i;
	
	map = (char **)malloc(ft_maplen(file) * sizeof(char *));
	fd = open(file, O_RDWR);
	if (!fd)
		return ;
	iter = get_next_line(fd);
	i = 0;
	while (iter)
	{
		map[i] = iter;
		free(iter);
		iter = get_next_line(fd);
		i++;
	}
	close(fd);
}