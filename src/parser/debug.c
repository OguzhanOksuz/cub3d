/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:25:07 by ooksuz            #+#    #+#             */
/*   Updated: 2023/10/21 22:41:53 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug_data(t_data *data)
{
	int	i;

	printf("\n----DEBUG----\n");
	printf("file\n");
	i = -1;
	while (data->file[++i])
		printf("%s", data->file[i]);
	printf("\nmap\n");
	i = -1;
	while (data->map[++i])
		printf("%s\n", data->map[i]);
	printf("\n--------\n");
	printf("NO = %s\n", data->no);
	printf("SO = %s\n", data->so);
	printf("EA = %s\n", data->ea);
	printf("WE = %s\n", data->we);
	printf("F = %s\nC = %s\n", data->f, data->c);
	printf("widht = %d\n", data->map_width);
	printf("height = %d\n", data->map_height);
	printf("x = %d\ny = %d\n", data->x, data->y);
	printf("dir = %d\n", data->dir);
	printf("floor = %d\n", data->floor);
	printf("ceiling = %d\n", data->ceiling);
	printf("\n-------------\n");
	system("leaks cub3d");
}
