/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:02:09 by mkaraden          #+#    #+#             */
/*   Updated: 2023/09/05 09:01:17 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Calculate the start and end points of the line on the screen
void	draw_textured_line(t_game *game, t_ray *ray, int x, int line_height)
{
	int				line_start;
	int				line_end;
	unsigned int	pixel_color;
	int				y;
	int				tex_y;

	line_start = (HEIGHT - line_height) / 2;
	line_end = (HEIGHT + line_height) / 2;
	y = line_start - 1;
	while (++y < line_end)
	{
		tex_y = get_tex_y(y, ray, line_height);
		pixel_color = get_pixel_color(tex_y, ray);
		my_mlx_pixel_put(&game->img, x, y, pixel_color);
	}
}

// Calculate the memory offset for the desired pixel in the texture and
// Extract the color from the texture using the offset
unsigned int	get_pixel_color(int tex_y, t_ray *ray)
{
	unsigned int	pixel_color;
	int				texture_byte_size;
	int				texture_offset;

	texture_byte_size = ray->texture->bits_per_pixel / 8;
	texture_offset = (tex_y * ray->texture->line_length) + ray->tex_x * texture_byte_size;
	pixel_color = *(unsigned int *)(ray->texture->addr + texture_offset);
	return (pixel_color);
}

// Calculate the proportion of y within the line_height
// and scale it by texture_height
// and ensure it is within the bounds of the texture
int	get_tex_y(int y, t_ray *ray, int line_height)
{
	double	d;
	double	half_screen_height;
	double	half_line_height;
	double	texture_height;
	int		tex_y;

	half_screen_height = HEIGHT / 2.0;
	half_line_height = line_height / 2.0;
	texture_height = (double)ray->texture->height;
	d = (y - half_screen_height + half_line_height) * texture_height / line_height;
	tex_y = (int)d;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture_height)
		tex_y = texture_height - 1;
	return (tex_y);
}

void	draw_floor_ceiling(t_game *game, int x, int lineHeight)
{
	int	start;
	int	end;
	int	y;

	start = (HEIGHT - lineHeight) / 2;
	end = (HEIGHT + lineHeight) / 2;
	y = -1;
	while (++y < start)
		my_mlx_pixel_put(&game->img, x, y, game->data->ceiling);
	y = end - 1;
	while (++y < HEIGHT)
		my_mlx_pixel_put(&game->img, x, y, game->data->floor);
}
