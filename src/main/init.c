/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:37:19 by mkaraden          #+#    #+#             */
/*   Updated: 2023/08/19 18:32:31 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	init_stuff(t_game *game)
{
	init_win(game);
	init_textures(game, game->data);

	
									
}

void set_dir(t_game *game, int dir)
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


void	init_win(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Raycaster");
	game->player.x = game->data->y; //2 //ozi ters almis
	game->player.y = game->data->x;   //2
	game->player.dir = M_PI / 4;
	set_dir(game, game->data->dir);

	game->map_size = game->data->map_width;

	for (int j = 0; j < game->map_size; j++)
		printf("%s\n", game->data->map[j]);

	game->img.img = mlx_new_image(game->mlx, 800, 600); 
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
									  &game->img.endian);
	
}

void	init_textures(t_game *game, t_data *data)
{
	game->textures[NORTH].img = mlx_xpm_file_to_image(game->mlx, data->no, &(game->textures[0].width), &(game->textures[0].height));
	game->textures[NORTH].addr = mlx_get_data_addr(game->textures[0].img, &(game->textures[0].bits_per_pixel), &(game->textures[0].line_length), &(game->textures[0].endian));
	
	game->textures[SOUTH].img = mlx_xpm_file_to_image(game->mlx, data->so, &(game->textures[1].width), &(game->textures[1].height));
	game->textures[SOUTH].addr = mlx_get_data_addr(game->textures[1].img, &(game->textures[1].bits_per_pixel), &(game->textures[1].line_length), &(game->textures[1].endian));

	game->textures[EAST].img = mlx_xpm_file_to_image(game->mlx, data->ea, &(game->textures[2].width), &(game->textures[2].height));
	game->textures[EAST].addr = mlx_get_data_addr(game->textures[2].img, &(game->textures[2].bits_per_pixel), &(game->textures[2].line_length), &(game->textures[2].endian));

	game->textures[WEST].img = mlx_xpm_file_to_image(game->mlx, data->we, &(game->textures[3].width), &(game->textures[3].height));
	game->textures[WEST].addr = mlx_get_data_addr(game->textures[3].img, &(game->textures[3].bits_per_pixel), &(game->textures[3].line_length), &(game->textures[3].endian));

	game->textures[M_BG].img = mlx_xpm_file_to_image(game->mlx, "assests/minimap/mbg.xpm", &(game->textures[6].width), &(game->textures[6].height));
	game->textures[M_BG].addr = mlx_get_data_addr(game->textures[6].img, &(game->textures[6].bits_per_pixel), &(game->textures[6].line_length), &(game->textures[6].endian));

	game->textures[M_W].img = mlx_xpm_file_to_image(game->mlx, "assests/minimap/mw.xpm", &(game->textures[7].width), &(game->textures[7].height));
	game->textures[M_W].addr = mlx_get_data_addr(game->textures[7].img, &(game->textures[7].bits_per_pixel), &(game->textures[7].line_length), &(game->textures[7].endian));

	game->textures[M_P].img = mlx_xpm_file_to_image(game->mlx, "assests/minimap/mp.xpm", &(game->textures[8].width), &(game->textures[8].height));
	game->textures[M_P].addr = mlx_get_data_addr(game->textures[8].img, &(game->textures[8].bits_per_pixel), &(game->textures[8].line_length), &(game->textures[8].endian));
}

void	init_textures2(t_game *game)
{
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
	
	game->textures[NORTH].img = mlx_xpm_file_to_image(game->mlx, txt[4], &(game->textures[0].width), &(game->textures[0].height));
	game->textures[NORTH].addr = mlx_get_data_addr(game->textures[0].img, &(game->textures[0].bits_per_pixel), &(game->textures[0].line_length), &(game->textures[0].endian));
	
	game->textures[SOUTH].img = mlx_xpm_file_to_image(game->mlx, txt[4], &(game->textures[1].width), &(game->textures[1].height));
	game->textures[SOUTH].addr = mlx_get_data_addr(game->textures[1].img, &(game->textures[1].bits_per_pixel), &(game->textures[1].line_length), &(game->textures[1].endian));

	game->textures[EAST].img = mlx_xpm_file_to_image(game->mlx, txt[4], &(game->textures[2].width), &(game->textures[2].height));
	game->textures[EAST].addr = mlx_get_data_addr(game->textures[2].img, &(game->textures[2].bits_per_pixel), &(game->textures[2].line_length), &(game->textures[2].endian));

	game->textures[WEST].img = mlx_xpm_file_to_image(game->mlx, txt[4], &(game->textures[3].width), &(game->textures[3].height));
	game->textures[WEST].addr = mlx_get_data_addr(game->textures[3].img, &(game->textures[3].bits_per_pixel), &(game->textures[3].line_length), &(game->textures[3].endian));

	game->textures[FLOOR].img = mlx_xpm_file_to_image(game->mlx, txt[5], &(game->textures[4].width), &(game->textures[4].height));
	game->textures[FLOOR].addr = mlx_get_data_addr(game->textures[4].img, &(game->textures[4].bits_per_pixel), &(game->textures[4].line_length), &(game->textures[4].endian));

	game->textures[CEILING].img = mlx_xpm_file_to_image(game->mlx, txt[4], &(game->textures[5].width), &(game->textures[5].height));
	game->textures[CEILING].addr = mlx_get_data_addr(game->textures[5].img, &(game->textures[5].bits_per_pixel), &(game->textures[5].line_length), &(game->textures[5].endian));

	game->textures[M_BG].img = mlx_xpm_file_to_image(game->mlx, txt[M_BG], &(game->textures[6].width), &(game->textures[6].height));
	game->textures[M_BG].addr = mlx_get_data_addr(game->textures[6].img, &(game->textures[6].bits_per_pixel), &(game->textures[6].line_length), &(game->textures[6].endian));

	game->textures[M_W].img = mlx_xpm_file_to_image(game->mlx, txt[M_W], &(game->textures[7].width), &(game->textures[7].height));
	game->textures[M_W].addr = mlx_get_data_addr(game->textures[7].img, &(game->textures[7].bits_per_pixel), &(game->textures[7].line_length), &(game->textures[7].endian));

	game->textures[M_P].img = mlx_xpm_file_to_image(game->mlx, txt[M_P], &(game->textures[8].width), &(game->textures[8].height));
	game->textures[M_P].addr = mlx_get_data_addr(game->textures[8].img, &(game->textures[8].bits_per_pixel), &(game->textures[8].line_length), &(game->textures[8].endian));
}