/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:13:00 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/10 19:11:15 by mkaraden         ###   ########.fr       */
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

int map[MAP_SIZE][MAP_SIZE] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};


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



#endif