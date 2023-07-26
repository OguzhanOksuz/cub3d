/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:57:21 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/26 18:21:46 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	draw_minimap(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < MAP_SIZE)
	{
		j = 0;
		while (j < MAP_SIZE)
		{
			draw_tile(game, i, j);
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(game->mlx, game->win, game->textures[M_P].img,
					(game->player.y * 8), (game->player.x * 8));
	
	
}

void	draw_tile(t_game *game, int i, int j)
{
	if (map[j][i] == 1)
		mlx_put_image_to_window(game->mlx, game->win, game->textures[M_W].img,
					(j * 8), (i * 8));
	else if (map[j][i] == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->textures[M_BG].img,
					(j * 8), (i * 8));

}