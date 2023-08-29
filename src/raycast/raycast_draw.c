/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:02:09 by mkaraden          #+#    #+#             */
/*   Updated: 2023/08/29 17:23:40 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void draw_textured_line(t_game *game, t_ray *ray, int x, int lineHeight)
{
    // Calculate the start and end points of the line on the screen
    int lineStart = (HEIGHT - lineHeight) / 2;
    int lineEnd = (HEIGHT + lineHeight) / 2;

    // Constants for the texture Y-coordinate calculation
    double textureHeight = (double)ray->texture->height;
    double halfScreenHeight = HEIGHT / 2.0;
    double halfLineHeight = lineHeight / 2.0;
    int textureByteSize = ray->texture->bits_per_pixel / 8;

    for (int y = lineStart; y < lineEnd; y++)
    {
        // Calculate the proportion of y within the lineHeight and scale it by textureHeight
        double d = (y - halfScreenHeight + halfLineHeight) * textureHeight / lineHeight;
        int texY = (int)d;
        
        // Ensure the texY is within the bounds of the texture
        if(texY < 0) texY = 0;
        if(texY >= textureHeight) texY = textureHeight - 1;

        // Calculate the memory offset for the desired pixel in the texture
        int textureOffset = texY * ray->texture->line_length + ray->tex_x * textureByteSize;
        
        // Extract the color from the texture using the offset
        unsigned int pixelColor = *(unsigned int *)(ray->texture->addr + textureOffset);
        
        // Draw the pixel on the screen at the given x,y position
        my_mlx_pixel_put(&game->img, x, y, pixelColor);
    }
}

void draw_floor_ceiling(t_game *game,int x, int lineHeight)
{
	int start = (HEIGHT - lineHeight) / 2;
	int end = (HEIGHT + lineHeight) / 2;

	// Draw the ceiling from 0 to the start of the wall.
	for (int y = 0; y < start; y++)
		my_mlx_pixel_put(&game->img, x, y, game->data->ceiling); // Blueish color for the ceiling. game->data->ceiling

	// Draw the floor from the end of the wall to the bottom of the screen.
	for (int y = end; y < HEIGHT; y++)
		my_mlx_pixel_put(&game->img, x, y, game->data->floor); // Brownish color for the floor. game->data->floor
}

void clearimg(t_game *game)
{
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			my_mlx_pixel_put(&(game->img), i, j, 0x00000000);
		}
	}
}


void my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
		
	char *dst;
	int offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}