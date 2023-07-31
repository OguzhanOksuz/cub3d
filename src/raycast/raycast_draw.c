/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:02:09 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/31 16:03:59 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_textured_line(t_game *game, t_ray *ray, int x, int lineHeight)
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

void draw_floor_ceiling(t_game *game,int x, int lineHeight)
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


void draw_floor_ceiling_textured(t_game *game, t_ray *ray, int x, int lineHeight)
{
	int start = (HEIGHT - lineHeight) / 2;
	int end = (HEIGHT + lineHeight) / 2;
	double wall_dist;
	double wallX = ray->perp_wall_dist * ray->ray_dir.x;
	

	// Draw the ceiling from 0 to the start of the wall.
	for (int y = 0; y < start; y++)
	{
		wall_dist = HEIGHT / (2.0 * y - HEIGHT);

		wall_dist = ray->perp_wall_dist;
		
		double weight = wall_dist / ray->perp_wall_dist;

		double tex_x = weight * wallX + (1.0 - weight) * game->player.x;
		double tex_y = weight * ray->map_y + (1.0 - weight) * game->player.y;

		int tex_x_int = (int)(tex_x * game->textures[CEILING].width) % game->textures[CEILING].width;
		int tex_y_int = (int)(tex_y * game->textures[CEILING].height) % game->textures[CEILING].height;

		int offset = tex_y_int * game->textures[CEILING].line_length + tex_x_int * (game->textures[CEILING].bits_per_pixel / 8);
		unsigned int color = *(unsigned int *)(game->textures[CEILING].addr + offset);

		my_mlx_pixel_put(&game->img, x, y, color);
	}

	// Draw the floor from the end of the wall to the bottom of the screen.
	for (int y = end; y < HEIGHT; y++)
	{
		wall_dist = HEIGHT / (2.0 * y - HEIGHT);

		wall_dist = ray->perp_wall_dist;
		
		double weight = wall_dist / ray->perp_wall_dist;

		

		double tex_x = weight * wallX + (1.0 - weight) * game->player.x;
		double tex_y = weight * ray->map_y + (1.0 - weight) * game->player.y;

		int tex_x_int = (int)(tex_x * game->textures[FLOOR].width) % game->textures[FLOOR].width;
		int tex_y_int = (int)(tex_y * game->textures[FLOOR].height) % game->textures[FLOOR].height;

		int offset = tex_y_int * game->textures[FLOOR].line_length + tex_x_int * (game->textures[FLOOR].bits_per_pixel / 8);
		unsigned int color = *(unsigned int *)(game->textures[FLOOR].addr + offset);

		my_mlx_pixel_put(&game->img, x, y, color);
	}

}