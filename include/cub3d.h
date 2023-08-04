/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:13:00 by mkaraden          #+#    #+#             */
/*   Updated: 2023/08/04 17:18:40 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "libs.h"


int map[MAP_SIZE][MAP_SIZE]; //gllobal map



//-------------MAIN-----------------------//

//hook
int key_hook(int key, t_game *game);

void	routine(t_game *game);

//debug
void	print_stats(t_game *game);
void	print_textures(t_game *game);

int	game_loop(t_game *game);

//init
void	init_stuff(t_game *game);
void	init_win(t_game *game);
void	init_textures(t_game *game);


//-------------PARSE-----------------------// //oguzhan
void	parse_cub(t_game *game, int ac, char **av);

//-------------RAYCAST--------------------//


void raycast(t_game *game);
void ray_step(t_ray *ray);

//calculate
void calculate_step_and_dist(t_game *game, t_ray *ray);
void calculate_perpetual(t_game *game, t_ray *ray, double angle);
void determine_texture(t_game *game, t_ray *ray, double angle);
void calculate_texture_x(t_game *game, t_ray *ray, double angle);

//draw
void draw_textured_line(t_game *game, t_ray *ray, int x, int lineHeight);
void draw_floor_ceiling(t_game *game,int x, int lineHeight);
void draw_floor_ceiling_textured(t_game *game, t_ray *ray, int x, int lineHeight);
void clearimg(t_game *game);
void my_mlx_pixel_put(t_img_data *data, int x, int y, int color);

//utils
void init_ray(t_game *game, t_ray *ray, double angle);
int is_boundary_violated(t_ray *ray);


//minimap
void	draw_minimap(t_game *game);
void	draw_tile(t_game *game, int i, int j);


#endif