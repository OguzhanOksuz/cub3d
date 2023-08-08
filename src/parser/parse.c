/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:48:01 by mkaraden          #+#    #+#             */
/*   Updated: 2023/08/08 21:51:51 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_cub(t_data *data, int ac, char **av)
{
	if (ac == 2)
	{
		printf("OMG\n");
		if (ft_strcmp(ft_strrchr(av[1], '.') + 1, "cub") != 0)
			ft_error(ERR_FILE, data);
		printf("WTF\n");
		map_check(data, av[1]);
//		init_map(data, av[1]);
	}
	else
		ft_error(ERR_AC, data);
}
