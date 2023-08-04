/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:38:07 by mkaraden          #+#    #+#             */
/*   Updated: 2023/08/04 17:19:47 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[MAP_SIZE][MAP_SIZE] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

//asil
int main(int ac, char **av)
{
	t_game	*game = malloc(sizeof(t_game));
	parse_cub(game, ac, av); //game->data
	init_stuff(game);
	mlx_hook(game->win, 2, 0, key_hook, game);
	routine(game);
	mlx_loop(game->mlx);
	return (0);
}


//temp
int main2(void)
{
	t_game game;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Raycaster");
	game.player.x = 2;
	game.player.y = 2;
	game.player.dir = M_PI / 4;

	game.img.img = mlx_new_image(game.mlx, 800, 600);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length,
									  &game.img.endian);

	
	
	char *(txt[]) =
	{
		"assests/textures/NO.xpm",
 		"assests/textures/SO.xpm",
  		"assests/textures/EA.xpm",
  		"assests/textures/WE.xpm",
		"assests/textures/brick.xpm", //4
		"assests/textures/floor.xpm",
		
		"assests/minimap/mbg.xpm",
		"assests/minimap/mw.xpm",
		"assests/minimap/mp.xpm",
		
		"assests/textures/KU.xpm",
 		"assests/textures/GU.xpm",
  		"assests/textures/DO.xpm",
  		"assests/textures/BA.xpm"
	};
	
	game.textures[NORTH].img = mlx_xpm_file_to_image(game.mlx, txt[4], &game.textures[0].width, &game.textures[0].height);
	game.textures[NORTH].addr = mlx_get_data_addr(game.textures[0].img, &game.textures[0].bits_per_pixel, &game.textures[0].line_length, &game.textures[0].endian);
	
	game.textures[SOUTH].img = mlx_xpm_file_to_image(game.mlx, txt[4], &game.textures[1].width, &game.textures[1].height);
	game.textures[SOUTH].addr = mlx_get_data_addr(game.textures[1].img, &game.textures[1].bits_per_pixel, &game.textures[1].line_length, &game.textures[1].endian);

	game.textures[EAST].img = mlx_xpm_file_to_image(game.mlx, txt[4], &game.textures[2].width, &game.textures[2].height);
	game.textures[EAST].addr = mlx_get_data_addr(game.textures[2].img, &game.textures[2].bits_per_pixel, &game.textures[2].line_length, &game.textures[2].endian);

	game.textures[WEST].img = mlx_xpm_file_to_image(game.mlx, txt[4], &game.textures[3].width, &game.textures[3].height);
	game.textures[WEST].addr = mlx_get_data_addr(game.textures[3].img, &game.textures[3].bits_per_pixel, &game.textures[3].line_length, &game.textures[3].endian);

	game.textures[FLOOR].img = mlx_xpm_file_to_image(game.mlx, txt[5], &game.textures[4].width, &game.textures[4].height);
	game.textures[FLOOR].addr = mlx_get_data_addr(game.textures[4].img, &game.textures[4].bits_per_pixel, &game.textures[4].line_length, &game.textures[4].endian);

	game.textures[CEILING].img = mlx_xpm_file_to_image(game.mlx, txt[4], &game.textures[5].width, &game.textures[5].height);
	game.textures[CEILING].addr = mlx_get_data_addr(game.textures[5].img, &game.textures[5].bits_per_pixel, &game.textures[5].line_length, &game.textures[5].endian);

	game.textures[M_BG].img = mlx_xpm_file_to_image(game.mlx, txt[M_BG], &game.textures[6].width, &game.textures[6].height);
	game.textures[M_BG].addr = mlx_get_data_addr(game.textures[6].img, &game.textures[6].bits_per_pixel, &game.textures[6].line_length, &game.textures[6].endian);

	game.textures[M_W].img = mlx_xpm_file_to_image(game.mlx, txt[M_W], &game.textures[7].width, &game.textures[7].height);
	game.textures[M_W].addr = mlx_get_data_addr(game.textures[7].img, &game.textures[7].bits_per_pixel, &game.textures[7].line_length, &game.textures[7].endian);

	game.textures[M_P].img = mlx_xpm_file_to_image(game.mlx, txt[M_P], &game.textures[8].width, &game.textures[8].height);
	game.textures[M_P].addr = mlx_get_data_addr(game.textures[8].img, &game.textures[8].bits_per_pixel, &game.textures[8].line_length, &game.textures[8].endian);
	

	mlx_hook(game.win, 2, 0, key_hook, &game);
	raycast(&game);
	mlx_loop(game.mlx);
	
	return (0);
}


