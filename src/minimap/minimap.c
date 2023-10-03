/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:57:21 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/03 16:52:59 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;

	if (!(game->debug))
		return;
	x = 0;
	y = 0;
	while (y < game->map_size)
	{
		x = 0;
		while (x < game->map_size)
		{
			draw_tile(game, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->textures[M_P].img,
		((game->player.x - 0.5) * 8), ((game->player.y - 0.5) * 8));
}

void	draw_tile(t_game *game, int x, int y)
{
	if (game->data->map[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->textures[M_W].img,
			(x * 8), (y * 8));
	else if (game->data->map[y][x] == '0')
		mlx_put_image_to_window(game->mlx, game->win, game->textures[M_BG].img,
			(x * 8), (y * 8));
}
