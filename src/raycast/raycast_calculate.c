/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calculate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:00:43 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/18 17:25:43 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void calculate_perpetual(Game *game, t_ray *ray, double angle) 
{
	double wallX = 0;
	
	if (ray->hit && ray->side == 0)
	{
		ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x) / 2) / ray->ray_dir.x;	
	}
	else if (ray->hit)
	{
		ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y) / 2) / ray->ray_dir.y;
	}
	else
		ray->perp_wall_dist = HEIGHT;
	
	// Correct the "fishbowl effect"
	ray->perp_wall_dist *= cos(game->player.dir - angle);

}


void calculate_texture_x(Game *game, t_ray *ray, double angle)
{
	double wallX = 0;
	
	if (ray->hit && ray->side == 0)
	{		
		wallX = game->player.y + ray->perp_wall_dist * ray->ray_dir.y;
		wallX -=floor((ray->map_x));
	}
	else if (ray->hit)
	{	
		wallX = game->player.x + ray->perp_wall_dist * ray->ray_dir.x;
		wallX -=floor((ray->map_y));
	}
	
	wallX -= floor((wallX));

	ray->tex_x = (int)(wallX * (double)(ray->texture->width));
	if ((ray->side == 0 && ray->ray_dir.x > 0) || (ray->side == 1 && ray->ray_dir.y < 0))
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
}

// Assign the texture based on the wall hit
void determine_texture(Game *game, t_ray *ray, double angle) 
{
	// If the ray hit a wall on the x-axis (East/West wall)
	if(ray->side == 0)
	{ 
    	if(ray->ray_dir.x > 0) // Check the direction of the ray
        	ray->texture = &game->textures[EAST];
    	else
        	ray->texture = &game->textures[WEST];
	}
	// If the ray hit a wall on the y-axis (North/South wall)
	else
	{ 
    	if(ray->ray_dir.y > 0) // Check the direction of the ray
        	ray->texture = &game->textures[NORTH];
    	else
        	ray->texture = &game->textures[SOUTH];
	}
}