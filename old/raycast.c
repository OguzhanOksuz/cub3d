/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:24:09 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/11 20:33:11 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"




void init_ray(Game *game, t_ray *ray, double angle)
{
	ray->ray_dir.x = cos(angle);
	ray->ray_dir.y = sin(angle);

	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;

	ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	ray->delta_dist.y = fabs(1 / ray->ray_dir.y);

	ray->hit = 0;
}

void calculate_step_and_dist(Game *game, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (game->player.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist.x;
	}

	if (ray->ray_dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (game->player.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist.y;
	}
}

void calculate_perpetual_and_color(Game *game, t_ray *ray, double angle)
{
	if (ray->hit && ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x) / 2) / ray->ray_dir.x;
	else if (ray->hit)
		ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y) / 2) / ray->ray_dir.y;
	else
		ray->perp_wall_dist = HEIGHT;

	// Correct the "fishbowl effect"
	ray->perp_wall_dist *= cos(game->player.dir - angle);


	if (ray->side == 0)										 // East or west wall.
		ray->color = ray->ray_dir.x > 0 ? RED : GREEN; // Red for east, green for west.
	else													 // North or south wall.
		ray->color = ray->ray_dir.y > 0 ? BLUE : YELLOW; // Blue for north, yellow for south.
	
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

//bir step ileri
void ray_step(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

//boudnary check
int is_boundary_violated(t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= MAP_SIZE || ray->map_y < 0 || ray->map_y >= MAP_SIZE)
	{
		return 1;
	}
	return 0;
}

void raycast(Game *game)
{
	clearimg(game);
	double angle_step = FOV / WIDTH;
	double angle = game->player.dir - FOV / 2;
	t_ray ray;
	
	for (int x = 0; x < WIDTH; x++, angle += angle_step)
	{
		init_ray(game, &ray, angle);
		calculate_step_and_dist(game, &ray);
		
		while (ray.hit == 0)
		{
			ray_step(&ray);
						
			// boundary checks
			if (is_boundary_violated(&ray) || map[ray.map_y][ray.map_x] > 0)
				ray.hit = 1;
		}

		calculate_perpetual_and_color(game, &ray, angle);
		
		int lineHeight = (int)(HEIGHT / ray.perp_wall_dist);
		
		draw_line(game, x, lineHeight, ray.color);
		draw_floor_ceiling(game, x, lineHeight);
	}
}
