/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:15:04 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/05 17:32:28 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_error(int num)
{
	if (num == ERROR_DEF)
		printf("unspecified error");
	else if (num == ERROR_AC)
		printf("invalid arg count");
	else if (num == ERROR_FILE)
		printf("invalid file");
	else if (num == ERROR_CHAR)
		printf("invalid char at file");
	else if (num == ERROR_WALLS)
		printf("map is not surrounded by walls");


	exit(1);
}

int	ft_maplen(char *file)
{
	char	*iter;
	int		fd;
	int		i;

	fd = open(file, O_RDWR);
	if (!fd)
		return ;
	iter = get_next_line(fd);
	i = 0;
	while (iter)
	{
		free(iter);
		iter = get_next_line(fd);
		i++;
	}
	return (i);
}