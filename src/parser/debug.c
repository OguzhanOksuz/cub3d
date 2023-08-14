/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:25:07 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/14 18:07:31 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug_data(t_data *data)
{
	printf("\n----DEBUG----\n");
	printf("file\n");
	for (int i = 0; data->file[i]; i++)
		printf("%s", data->file[i]);
	printf("\nmap\n");
	for (int j = 0; data->map[j]; j++)
		printf("%s\n", data->map[j]);
	printf("\n--------\n");
	printf("NO = %s\n", data->no);
	printf("SO = %s\n", data->so);
	printf("EA = %s\n", data->ea);
	printf("WE = %s\n", data->we);
	printf("F = %s\n", data->f);
	printf("C = %s\n", data->c);
	printf("widht = %d\n", data->map_width);
	printf("height = %d\n", data->map_height);
	printf("x = %d\n", data->x);
	printf("y = %d\n", data->y);
	printf("dir = %d\n", data->dir);
	printf("floor = %d\n", data->floor);
	printf("ceiling = %d\n", data->ceiling);
	printf("\n-------------\n");
}
