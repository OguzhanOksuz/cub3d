/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calculate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:00:43 by mkaraden          #+#    #+#             */
/*   Updated: 2023/09/05 08:55:24 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//calculate x,y step and nearest x,y distances
void	calculate_step_and_dist(t_game *game, t_ray *ray)
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

//perp distance
void	calculate_perpetual(t_game *game, t_ray *ray, double angle)
{	
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x) / 2) / ray->ray_dir.x;	
	else
		ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y) / 2) / ray->ray_dir.y;
}

// Assign the texture based on the wall hit
void	determine_texture(t_game *game, t_ray *ray, double angle)
{
	// If the ray hit a wall on the x-axis (East/West wall)
	if(ray->side == 0)
	{ 
    	if(ray->ray_dir.x > 0) // Check the direction of the ray
        	ray->texture = &(game->textures[EAST]);
    	else
        	ray->texture = &(game->textures[WEST]);
	}
	// If the ray hit a wall on the y-axis (North/South wall)
	else
	{ 
    	if(ray->ray_dir.y > 0) // Check the direction of the ray
        	ray->texture = &(game->textures[SOUTH]);
    	else
        	ray->texture = &(game->textures[NORTH]);
	}
}

//slack de resmi var
void	calculate_texture_x(t_game *game, t_ray *ray, double angle)
{
	double wallX;
	
	if (ray->side == 0) //EAST WEST
		wallX = game->player.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		wallX = game->player.x + ray->perp_wall_dist * ray->ray_dir.x;
	
	wallX -= floor((wallX));
	
	ray->tex_x = (int)(wallX * (double)(ray->texture->width));
	
	//mirror check
	if ((ray->side == 0 && ray->ray_dir.x < 0) || (ray->side == 1 && ray->ray_dir.y > 0))
    	ray->tex_x = ray->texture->width - ray->tex_x - 1;
	
	// Correct the "fishbowl effect"
	ray->perp_wall_dist *= cos(game->player.dir - angle);
}
