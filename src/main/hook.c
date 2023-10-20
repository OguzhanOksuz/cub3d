/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:51:01 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/19 19:03:32 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_press(int key, t_game *game)
{
	printf("PRESSED KEY: %d\n", key);
	game->key = key;
	if (key == 3)
		game->debug = !(game->debug);
	if (key == 53)
		data_error(ERR_EXIT, game);
	return (0);
}

int	ft_release(int key, t_game *game)
{
	printf("RELEASED KEY: %d\n", key);
	if (key == game->key)
		game->key = -1;
	routine(game);
	return (0);
}

//@param player is used as temp
//original player in @param game is updated in ft_try_move
//if there is no wall in new pos
void	ft_move(t_player player, int dir, t_game *game)
{
	if (dir == NORTH)
	{
		player.x += player.dir_x * MOVE_SPEED;
		player.y += player.dir_y * MOVE_SPEED;
	}
	if (dir == SOUTH)
	{
		player.x -= player.dir_x * MOVE_SPEED;
		player.y -= player.dir_y * MOVE_SPEED;
	}
	if (dir == EAST)
	{
		player.x -= player.dir_y * MOVE_SPEED;
		player.y += player.dir_x * MOVE_SPEED;
	}
	if (dir == WEST)
	{
		player.x += player.dir_y * MOVE_SPEED;
		player.y -= player.dir_x * MOVE_SPEED;
	}
	ft_collision(player.x, player.y, &(game->player), game->data->map);
}

//update dir and keep the angle between 0 and 2π
//0.1
void	ft_turn(t_player *player, int dir)
{
	if (dir == WEST)
	{
		player->dir -= TURN_SPEED;
		if (player->dir < 0)
			player->dir += 2 * M_PI;
	}
	if (dir == EAST)
	{
		player->dir += TURN_SPEED;
		if (player->dir > 2 * M_PI)
			player->dir -= 2 * M_PI;
	}
}

//collison check
//printf("X: %f Y: %f HIT TO %c\n", new_x, new_y, map[(int)new_y][(int)new_x]);
void	ft_collision(double new_x, double new_y, t_player *player, char **map)
{
	if (map[(int)(new_y)][(int)(new_x)] != '1')
	{
		player->x = new_x;
		player->y = new_y;
	}
}
