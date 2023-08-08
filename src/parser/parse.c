/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:48:01 by mkaraden          #+#    #+#             */
/*   Updated: 2023/08/08 17:26:45 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_cub(t_game *game, int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_error(ERR_MALLOC, game);
	if (ac == 2)
	{
		if (ft_strcmp(av[1] + ft_strrchr(av[1]) + 1, ".cub") == 0)
			ft_error(ERR_FILE, game);
		map_check(data, av[1]);
		init_map(data, av[1]);
	}
	else
		ft_error(ERR_AC, game);
}
