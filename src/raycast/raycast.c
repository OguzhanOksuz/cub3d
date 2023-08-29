/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 23:23:34 by mkaraden          #+#    #+#             */
/*   Updated: 2023/08/29 17:34:04 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_game *game)
{
	double	angle_step = FOV / WIDTH;
	double	angle = game->player.dir - FOV / 2;
	t_ray	ray;
	
	for (int x = 0; x < WIDTH; x++, angle += angle_step)
	{
		init_ray(game, &ray, angle);
		calculate_step_and_dist(game, &ray);
	
		while (ray.hit == 0)
		{
			ray_step(&ray);
			if (is_hit(&ray, game))
				ray.hit = 1;
		}
		
		calculate_perpetual(game, &ray, angle);
		determine_texture(game, &ray, angle);
		calculate_texture_x(game, &ray, angle);

		int line_height = (int)(HEIGHT / ray.perp_wall_dist);
		
		draw_textured_line(game, &ray, x, line_height);
		draw_floor_ceiling(game, x, line_height);
	}
}

//take one step
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
