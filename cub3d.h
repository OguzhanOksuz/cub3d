/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:13:00 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/11 20:33:51 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <sys/time.h>

# include "mlx/mlx.h"
# include "gnl/get_next_line.h"


typedef enum
{
	ERROR_DEF,
	ERROR_AC,
	ERROR_FILE,
	ERROR_CHAR,
	ERROR_WALLS,
}				errType;


#include "mlx/mlx.h"
#include "math.h"
#include <stdlib.h>

#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define MAP_SIZE 10
#define FOV M_PI / 3
#define RAY_STEP 0.01

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} img_data;

typedef struct t_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;
} txt_data;

typedef struct
{
	double x;
	double y;
	double dir;
} Player;

typedef struct
{
	void *mlx;
	void *win;
	Player player;
	img_data img;
	//int map[MAP_SIZE][MAP_SIZE];

	txt_data textures[4];
} Game;

int map[MAP_SIZE][MAP_SIZE]; //gllobal map

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct s_ray
{
	t_point	ray_dir;
	t_point	side_dist;
	t_point	delta_dist;
	
	int		map_x;
	int		map_y;
	
	double	perp_wall_dist;
	
	int		step_x;
	int		step_y;
	
	int		side;
	double	ratio;
	int		hit;
	
	int		color;
	
}			t_ray;

typedef struct {
    double x;
    double y;
    double dirX;
    double dirY;
    double perpWallDist;
    int hit;
    int side;
} Ray;

typedef enum {
    RED = 0x00FF0000,      // Red for east
    GREEN = 0x0000FF00,    // Green for west
    BLUE = 0x000000FF,     // Blue for north
    YELLOW = 0x00FFFF00,   // Yellow for south
    CEILING_BLUE = 0x00AAAAFF, // Blueish color for the ceiling
    FLOOR_BROWN = 0x00660000   // Brownish color for the floor
} Color;

//RAYCAST
void raycast(Game *game);

int is_boundary_violated(t_ray *ray);
void ray_step(t_ray *ray);
void draw_floor_ceiling(Game *game,int x, int lineHeight);
void calculate_perpetual_and_color(Game *game, t_ray *ray, double angle);
void calculate_step_and_dist(Game *game, t_ray *ray);
void init_ray(Game *game, t_ray *ray, double angle);

//DRAW
void my_mlx_pixel_put(img_data *data, int x, int y, int color);
void draw_line(Game *game, int x, double height, int color);
void clearimg(Game *game);

#endif