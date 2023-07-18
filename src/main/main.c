/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:38:07 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/18 16:33:39 by mkaraden         ###   ########.fr       */
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

int main(void)
{
	Game game;
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

		"assests/textures/KU.xpm",
 		"assests/textures/GU.xpm",
  		"assests/textures/DO.xpm",
  		"assests/textures/BA.xpm",	
  		"assests/textures/brick.xpm",
		"assests/textures/NO.xpm",
 		"assests/textures/SO.xpm",
  		"assests/textures/EA.xpm",
  		"assests/textures/WE.xpm"
	
	};
	
	game.textures[NORTH].img = mlx_xpm_file_to_image(game.mlx, txt[NORTH], &game.textures[0].width, &game.textures[0].height);
	game.textures[NORTH].addr = mlx_get_data_addr(game.textures[0].img, &game.textures[0].bits_per_pixel, &game.textures[0].line_length, &game.textures[0].endian);
	
	game.textures[SOUTH].img = mlx_xpm_file_to_image(game.mlx, txt[SOUTH], &game.textures[1].width, &game.textures[1].height);
	game.textures[SOUTH].addr = mlx_get_data_addr(game.textures[1].img, &game.textures[1].bits_per_pixel, &game.textures[1].line_length, &game.textures[1].endian);

	game.textures[EAST].img = mlx_xpm_file_to_image(game.mlx, txt[EAST], &game.textures[2].width, &game.textures[2].height);
	game.textures[EAST].addr = mlx_get_data_addr(game.textures[2].img, &game.textures[2].bits_per_pixel, &game.textures[2].line_length, &game.textures[2].endian);

	game.textures[WEST].img = mlx_xpm_file_to_image(game.mlx, txt[WEST], &game.textures[3].width, &game.textures[3].height);
	game.textures[WEST].addr = mlx_get_data_addr(game.textures[3].img, &game.textures[3].bits_per_pixel, &game.textures[3].line_length, &game.textures[3].endian);

	

	mlx_hook(game.win, 2, 0, key_hook, &game);
	raycast(&game);
	mlx_loop(game.mlx);
	return (0);
}

void draw_line(Game *game, int x, double height, int color)
{
	int start = (HEIGHT - height) / 2;
	int end = (HEIGHT + height) / 2;
	for (int y = start; y < end; y++)
		my_mlx_pixel_put(&game->img, x, y, color);
}


void raycastTextured(Game *game)
{
	clearimg(game);
	double angle_step = FOV / WIDTH; // ray count
	double angle = game->player.dir - FOV / 2;
	for (int x = 0; x < WIDTH; x++, angle += angle_step)
	{
		double dirX = cos(angle);
		double dirY = sin(angle);

		int mapX = (int)game->player.x;
		int mapY = (int)game->player.y;

		double sideDistX;
		double sideDistY;

		double deltaDistX = fabs(1 / dirX);
		double deltaDistY = fabs(1 / dirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (dirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
		}

		if (dirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			// add boundary checks here
			if (mapX < 0 || mapX >= MAP_SIZE || mapY < 0 || mapY >= MAP_SIZE)
			{
				hit = 1;
			}
			else if (map[mapY][mapX] > 0)
			{
				hit = 1;
			}
		}
		int lineHeight = 0;

		double wallX;
		if (side == 0)
			wallX = game->player.y + perpWallDist * dirY;
		else
			wallX = game->player.x + perpWallDist * dirX;
		wallX -= floor(wallX);

		if (hit)
		{
			// Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
			if (side == 0)
				perpWallDist = (mapX - game->player.x + (1 - stepX) / 2) / dirX;
			else
				perpWallDist = (mapY - game->player.y + (1 - stepY) / 2) / dirY;

			perpWallDist *= cos(game->player.dir - angle);

			// Calculate height of line to draw on screen
			lineHeight = (int)(HEIGHT / perpWallDist);

			// Calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + HEIGHT / 2;
			int drawEnd = lineHeight / 2 + HEIGHT / 2;

			// Texture rendering
			txt_data *texture;
			int texX;
			if (side == 0)
				texture = dirX > 0 ? &game->textures[2] : &game->textures[3]; // Choose east or west texture.
			else
				texture = dirY > 0 ? &game->textures[0] : &game->textures[1]; // Choose north or south texture.

			if (side == 0)
				texX = (int)(game->player.y + perpWallDist * dirY) % texture->width;
			else
				texX = (int)(game->player.x + perpWallDist * dirX) % texture->width;

			// Loop through every pixel of the stripe/screen column

			texX = (int)(wallX * (double)(texture->width));
			if (side == 0 && dirX > 0)
				texX = texture->width - texX - 1;
			if (side == 1 && dirY < 0)
				texX = texture->width - texX - 1;
			for (int y = drawStart; y < drawEnd; y++)
			{
				int d = y * 256 - HEIGHT * 128 + lineHeight * 128;
				int texY = ((d * texture->height) / lineHeight) / 256;
				int color = ((int *)(texture->addr))[texY * texture->line_length / 4 + texX];
				my_mlx_pixel_put(&game->img, x, y, color);
			}

			// The rest of your function remains unchanged ...
		}

		// FLOOR CEILING

		// Determine the start and end of the wall in this column.
		int start = (HEIGHT - lineHeight) / 2;
		int end = (HEIGHT + lineHeight) / 2;

		// Draw the ceiling from 0 to the start of the wall.
		for (int y = 0; y < start; y++)
			my_mlx_pixel_put(&game->img, x, y, 0x00AAAAFF); // Blueish color for the ceiling.

		// Draw the wall.
		// draw_line(game, x, lineHeight, 0x00FF0000);

		// Draw the floor from the end of the wall to the bottom of the screen.
		for (int y = end; y < HEIGHT; y++)
			my_mlx_pixel_put(&game->img, x, y, 0x00660000); // Brownish color for the floor.
	}
}



void raycast2(Game *game)
{
	clearimg(game);
	double angle_step = FOV / WIDTH; // ray count
	double angle = game->player.dir - FOV / 2;
	for (int x = 0; x < WIDTH; x++, angle += angle_step)
	{
		double ray_x = game->player.x;
		double ray_y = game->player.y;
		while (map[(int)ray_y][(int)ray_x] == 0) // game->map
		{
			ray_x += RAY_STEP * cos(angle);
			ray_y += RAY_STEP * sin(angle);
		}
		double dist = sqrt(pow(ray_x - game->player.x, 2) + pow(ray_y - game->player.y, 2));
		double corrected_dist = dist * cos(game->player.dir - angle);
		double wall_height = (1 / corrected_dist) * HEIGHT;
		draw_line(game, x, wall_height, 0x00FF0000);
	}
}

