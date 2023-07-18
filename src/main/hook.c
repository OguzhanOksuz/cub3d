/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:51:01 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/18 16:06:35 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_hook(int key, Game *game)
{
	printf("KEY: %d\n", key);
	if (key == 53) // Escape key
		exit(0);
	double dir_x = cos(game->player.dir);
	double dir_y = sin(game->player.dir);
	double speed = 0.1;
	if (key == KEY_W) // W
	{
		game->player.x += dir_x * speed;
		game->player.y += dir_y * speed;
	}
	else if (key == KEY_S) // S
	{
		game->player.x -= dir_x * speed;
		game->player.y -= dir_y * speed;
	}
	else if (key == KEY_A) // A
	{
		game->player.x += dir_y * speed;
		game->player.y -= dir_x * speed;
	}
	else if (key == KEY_D) // D
	{
		game->player.x -= dir_y * speed;
		game->player.y += dir_x * speed;
	}
	else if (key == ARR_L) // Left arrow key
	{
		game->player.dir -= 0.1;
		if (game->player.dir < 0) // Keep the angle between 0 and 2π
			game->player.dir += 2 * M_PI;
	}
	else if (key == ARR_R) // Right arrow key
	{
		game->player.dir += 0.1;
		if (game->player.dir > 2 * M_PI) // Keep the angle between 0 and 2π
			game->player.dir -= 2 * M_PI;
	}
	
	print_stats(game);
	
	mlx_clear_window(game->mlx, game->win);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);

	
	print_textures(game);

	return (0);
}

void	print_stats(Game *game)
{
	printf("\n\n--OMG Stats--\n\n");
	printf("dir = %f\n", game->player.dir);
	printf("\n-----XYZ------\n");
	printf("dir_x = %f\n", cos(game->player.dir));
	printf("dir_y = %f\n", sin(game->player.dir));
	printf("\n-----PPlayer------\n");
	printf("player_x = %f\n", game->player.x);
	printf("player_y = %f\n", game->player.y);
}

void	print_textures(Game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->textures[NORTH].img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures[SOUTH].img, 64, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures[EAST].img, 128, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures[WEST].img, 192, 0);
}