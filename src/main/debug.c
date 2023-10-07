/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:31:16 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/07 05:12:35 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DECIMAL_PLACES 4
#define MULTIPLIER 10000  // 10 raised to the power of DECIMAL_PLACES

void	print_stat(t_game *game, char *msg, int y, char *num)
{
	mlx_string_put(game->mlx, game->win, 700, y, RED, msg);
	mlx_string_put(game->mlx, game->win, 700, y + 10, RED, num);
	free(num);
}

void	print_stats(t_game *game)
{
	int	y;

	if (!(game->debug))
		return ;
	printf("\n\n--OMG Stats--\n\n");
	printf("dir = %f\n", game->player.dir);
	printf("\n-----XYZ------\n");
	printf("dir_x = %f\n", cos(game->player.dir));
	printf("dir_y = %f\n", sin(game->player.dir));
	printf("\n-----PPlayer------\n");
	printf("player_x = %f\n", game->player.x);
	printf("player_y = %f\n", game->player.y);
	y = 10;
	print_stat(game, "dir: ", y, dtoa(game->player.dir));
	print_stat(game, "dir_x: ", y + 30, dtoa(cos(game->player.dir)));
	print_stat(game, "dir_y: ", y + 60, dtoa(sin(game->player.dir)));
	print_stat(game, "player_x: ", y + 90, dtoa(game->player.x));
	print_stat(game, "player_y: ", y + 120, dtoa(game->player.y));
}
