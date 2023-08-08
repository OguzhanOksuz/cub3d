/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 11:35:42 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/08 18:33:12 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_check(t_game *game, char *src)
{
	int		fd;
	int		i;
	char	*tmp;
	char	**raw_map;

	fd = open(src, O_RDONLY);
	if (fd < 0)
		ft_error(ERR_FILE, game);
	i = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		free (tmp);
		tmp = get_next_line(fd);
		i++;
	}
	printf ("i = %d", i);
	check_contents(game, raw_map);
}
