/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:51:01 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/22 02:27:09 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//printf("PRESSED KEY: %d\n", key);
int	ft_press(int key, t_game *game)
{
	game->key = key;
	if (key == 3)
		game->debug = !(game->debug);
	if (key == 53)
		data_error(ERR_EXIT, game);
	return (0);
}

//printf("RELEASED KEY: %d\n", key);
int	ft_release(int key, t_game *game)
{
	if (key == game->key)
		game->key = -1;
	routine(game);
	return (0);
}

void	ft_move(t_player player, int dir, t_game *game)
{
	if (dir == NORTH)
	{
		player.x += player.dir_x * (MOVE_SPEED + OFFSET);
		player.y += player.dir_y * (MOVE_SPEED + OFFSET);
	}
	if (dir == SOUTH)
	{
		player.x -= player.dir_x * (MOVE_SPEED + OFFSET);
		player.y -= player.dir_y * (MOVE_SPEED + OFFSET);
	}
	if (dir == EAST)
	{
		player.x -= player.dir_y * (MOVE_SPEED + OFFSET);
		player.y += player.dir_x * (MOVE_SPEED + OFFSET);
	}
	if (dir == WEST)
	{
		player.x += player.dir_y * (MOVE_SPEED + OFFSET);
		player.y -= player.dir_x * (MOVE_SPEED + OFFSET);
	}
	if (is_collide(player.x, player.y, &(game->player), game->data->map))
		ft_move_fr(&(game->player), dir, game);
}

//@param player is used as temp
//original player in @param game is updated in ft_try_move
//if there is no wall in new pos
void	ft_move_fr(t_player *player, int dir, t_game *game)
{
	if (dir == NORTH)
	{
		player->x += player->dir_x * (MOVE_SPEED);
		player->y += player->dir_y * (MOVE_SPEED);
	}
	if (dir == SOUTH)
	{
		player->x -= player->dir_x * (MOVE_SPEED);
		player->y -= player->dir_y * (MOVE_SPEED);
	}
	if (dir == EAST)
	{
		player->x -= player->dir_y * (MOVE_SPEED);
		player->y += player->dir_x * (MOVE_SPEED);
	}
	if (dir == WEST)
	{
		player->x += player->dir_y * (MOVE_SPEED);
		player->y -= player->dir_x * (MOVE_SPEED);
	}
}

//collison check
//printf("X: %f Y: %f HIT TO %c\n", new_x, new_y, map[(int)new_y][(int)new_x]);
int	is_collide(double new_x, double new_y, t_player *player, char **map)
{
	if (map[(int)(new_y)][(int)(new_x)] != '1')
		return (1);
	return (0);
}

//collison check
//printf("X: %f Y: %f HIT TO %c\n", new_x, new_y, map[(int)new_y][(int)new_x]);
// void	ft_collision2(double new_x, double new_y, t_player *player, char **map)
// {
// 	if (map[(int)(new_y)][(int)(new_x)] != '1')
// 	{
// 		player->x = new_x - player->dir_x * OFFSET;
// 		player->y = new_y - player->dir_y * OFFSET;;
// 	}
// }
// void	ft_move2(t_player player, int dir, t_game *game)
// {
// 	if (dir == NORTH)
// 	{
// 		player.x += player.dir_x * (MOVE_SPEED);
// 		player.y += player.dir_y * (MOVE_SPEED);
// 	}
// 	if (dir == SOUTH)
// 	{
// 		player.x -= player.dir_x * (MOVE_SPEED);
// 		player.y -= player.dir_y * (MOVE_SPEED);
// 	}
// 	if (dir == EAST)
// 	{
// 		player.x -= player.dir_y * (MOVE_SPEED);
// 		player.y += player.dir_x * (MOVE_SPEED);
// 	}
// 	if (dir == WEST)
// 	{
// 		player.x += player.dir_y * (MOVE_SPEED);
// 		player.y -= player.dir_x * (MOVE_SPEED);
// 	}
// 	//ft_collision(player.x, player.y, &(game->player), game->data->map);
// }
