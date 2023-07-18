/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycat_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:03:46 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/18 14:04:14 by mkaraden         ###   ########.fr       */
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

//boudnary check
int is_boundary_violated(t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= MAP_SIZE || ray->map_y < 0 || ray->map_y >= MAP_SIZE)
	{
		return 1;
	}
	return 0;
}
