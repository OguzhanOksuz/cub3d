/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:38:07 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/19 19:39:27 by mkaraden         ###   ########.fr       */
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

/*int main2(int ac, char **av)
{
	if (ac != 2)
		ft_error(NULL, ERROR_DEF);
	parse_cub(av[1]);
	
}*/

int main(void)
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
		"assests/textures/brick.xpm",
		"assests/textures/floor.xpm",
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
	
	
	

	mlx_hook(game.win, 2, 0, key_hook, &game);
	raycast(&game);
	mlx_loop(game.mlx);
	
	return (0);
}


