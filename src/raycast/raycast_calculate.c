/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calculate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:00:43 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/21 00:27:15 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//calculate x,y step and nearest x,y distances
//ray->ray_dir.x < 0 left
//ray->ray_dir.y < 0 up
//side_dist distance between next map grid
//0.6 -> 0.4
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
//one step back because we are inside of the wall
void	calculate_perpetual(t_game *game, t_ray *ray, double angle)
{
	while (ray->hit == 0)
	{
		ray_step(ray);
		if (is_hit(ray, game))
			ray->hit = 1;
	}
	if (ray->side == EAST_WEST)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;	
}

//Assign the texture based on the wall hit
//side == 0 -> // If the ray hit a wall on the x-axis (East/West wall)
//side == 1 -> // If the ray hit a wall on the y-axis (North/South wall)
void	determine_texture(t_game *game, t_ray *ray, double angle)
{
	if (ray->side == EAST_WEST)
	{
		if (ray->ray_dir.x > 0)
			ray->texture = &(game->textures[EAST]);
		else
			ray->texture = &(game->textures[WEST]);
	}
	else
	{
		if (ray->ray_dir.y > 0)
			ray->texture = &(game->textures[SOUTH]);
		else
			ray->texture = &(game->textures[NORTH]);
	}
}

//slack de resmi var
void	calculate_texture_x(t_game *game, t_ray *ray, double angle)
{
	double	wall_x;

	if (ray->side == EAST_WEST)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir.x;
	wall_x -= floor((wall_x));
	ray->tex_x = (int)(wall_x * (double)(ray->texture->width));
	fix_mirror(ray);
}

//mirror check
//WEST or SOUTH
void	fix_mirror(t_ray *ray)
{
	if ((ray->side == 0 && ray->ray_dir.x < 0)
		|| (ray->side == 1 && ray->ray_dir.y > 0))
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
}
