/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:02:09 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/18 14:46:34 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_textured_line(Game *game, t_ray *ray, int x, int lineHeight)
{
	int start = (HEIGHT - lineHeight) / 2;
	int end = (HEIGHT + lineHeight) / 2;

	for (int y = start; y < end; y++)
	{
		int d = y * 256 - HEIGHT * 128 + lineHeight * 128;
		int tex_y = ((d * ray->texture->height) / lineHeight) / 256;
		
		// Calculate the offset for the pixel in the texture
		int offset = tex_y * ray->texture->line_length + ray->tex_x * (ray->texture->bits_per_pixel / 8);
		
		// Extract the color using the offset
		unsigned int color = *(unsigned int *)(ray->texture->addr + offset);
		
		my_mlx_pixel_put(&game->img, x, y, color);
	}
}

void draw_floor_ceiling(Game *game,int x, int lineHeight)
{
	int start = (HEIGHT - lineHeight) / 2;
	int end = (HEIGHT + lineHeight) / 2;

	// Draw the ceiling from 0 to the start of the wall.
	for (int y = 0; y < start; y++)
		my_mlx_pixel_put(&game->img, x, y, CEILING_BLUE); // Blueish color for the ceiling.

	// Draw the floor from the end of the wall to the bottom of the screen.
	for (int y = end; y < HEIGHT; y++)
		my_mlx_pixel_put(&game->img, x, y, FLOOR_BROWN); // Brownish color for the floor.
}

void clearimg(Game *game)
{
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			my_mlx_pixel_put(&game->img, i, j, 0x00000000);
		}
	}
}


void my_mlx_pixel_put(img_data *data, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	{
		return;
	}
	char *dst;
	int offset = (y * data->line_length + x * (data->bits_per_pixel / 8));

	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}