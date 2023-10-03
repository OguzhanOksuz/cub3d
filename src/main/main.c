/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:38:07 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/03 18:22:16 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//asil
//mlx_hook(game->win, 2, 0, key_hook, game);
int	main(int ac, char **av)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	parse_cub(game, ac, av);
	init_stuff(game);
	mlx_hook(game->win, 2, 0, key_hook, game);
	//mlx_hook(game->win, 2, 0, ft_press, game);
	//mlx_hook(game->win, 3, 0, ft_release, game);
	mlx_hook(game->win, 17, 1L << 2, data_error, game);
	//mlx_loop_hook(game->mlx, &ft_loop, game);
	//routine(game);
	mlx_loop(game->mlx);
	return (0);
}

int	key_hook(int key, t_game *game)
{
	game->player.dir_x = cos(game->player.dir);
	game->player.dir_y = sin(game->player.dir);
	if (key == KEY_W)
		ft_move(game->player, NORTH, game);
	else if (key == KEY_S)
		ft_move(game->player, SOUTH, game);
	else if (key == KEY_A)
		ft_move(game->player, WEST, game);
	else if (key == KEY_D)
		ft_move(game->player, EAST, game);
	else if (key == ARR_L)
		ft_turn(&(game->player), WEST);
	else if (key == ARR_R)
		ft_turn(&(game->player), EAST);
	else if (key == 3)
		game->debug = !(game->debug);
	if (key == 53)
		data_error(ERR_EXIT, game);
	routine(game);
	return (0);
}

int	ft_loop(t_game *game)
{
	game->player.dir_x = cos(game->player.dir);
	game->player.dir_y = sin(game->player.dir);
	routine(game);
	if (game->key == KEY_W)
		ft_move(game->player, NORTH, game);
	else if (game->key == KEY_S)
		ft_move(game->player, SOUTH, game);
	else if (game->key == KEY_A)
		ft_move(game->player, WEST, game);
	else if (game->key == KEY_D)
		ft_move(game->player, EAST, game);
	else if (game->key == ARR_L)
		ft_turn(&(game->player), WEST);
	else if (game->key == ARR_R)
		ft_turn(&(game->player), EAST);
	else if (game->key == 3)
		game->debug = !(game->debug);
	if (game->key == 53)
		data_error(ERR_EXIT, game);
	routine(game);
	return (0);
}

void	routine(t_game *game)
{
	clearimg(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	draw_minimap(game);
	print_stats(game);
}
