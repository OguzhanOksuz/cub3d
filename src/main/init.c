/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:37:19 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/21 23:55:37 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_stuff(t_game *game)
{
	init_win(game);
	init_textures(game, game->data);
}

//ozi ters almis x,y
//0.5 ekle ortalamak icin
//0.15
void	init_win(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	game->player.x = game->data->y + 0.5;
	game->player.y = game->data->x + 0.5;
	game->player.dir = M_PI / 4;
	set_dir(game, game->data->dir);
	game->debug = 0;
	game->key = -1;
	game->map_size = game->data->map_width;
	game->img.img = mlx_new_image(game->mlx, 800, 600);
	game->img.addr = mlx_get_data_addr(
			game->img.img,
			&game->img.bits_per_pixel,
			&game->img.line_length,
			&game->img.endian);
}

void	init_textures(t_game *game, t_data *data)
{
	load_texture(game, NORTH, data->no);
	load_texture(game, SOUTH, data->so);
	load_texture(game, EAST, data->ea);
	load_texture(game, WEST, data->we);
	load_texture(game, M_BG, "assests/minimap/mbg.xpm");
	load_texture(game, M_W, "assests/minimap/mw.xpm");
	load_texture(game, M_P, "assests/minimap/mp.xpm");
}

void	set_dir(t_game *game, int dir)
{
	if (dir == NORTH)
		game->player.dir = 1.5 * M_PI;
	else if (dir == SOUTH)
		game->player.dir = 0.5 * M_PI;
	else if (dir == EAST)
		game->player.dir = 0;
	else if (dir == WEST)
		game->player.dir = M_PI;
}

void	load_texture(t_game *game, int index, char *path)
{
	game->textures[index].img = mlx_xpm_file_to_image(
			game->mlx, path,
			&(game->textures[index].width),
			&(game->textures[index].height)
			);
	game->textures[index].addr = mlx_get_data_addr(
			game->textures[index].img,
			&(game->textures[index].bits_per_pixel),
			&(game->textures[index].line_length),
			&(game->textures[index].endian)
			);
}
