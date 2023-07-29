/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:13:00 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/29 13:26:31 by mkaraden         ###   ########.fr       */
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

# include "../mlx/mlx.h"
# include "../src/gnl/get_next_line.h"


typedef enum
{
	ERR_DEF,
	ERR_AC,
	ERR_FILE,
	
	ERR_CHAR,
	ERR_WALLS,
	ERR_SPACE, //mapte bosluk varsa diye char ile birlesiriebilir
	
	ERR_ORDER,
	ERR_PATH,
}				errType;

typedef enum
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
	M_BG,
	M_W,
	M_P
}				direction;

typedef struct s_data
{
	char	**map;
	int		map_width;
	int		map_height;
	
	int		dir; //direction enum dan ver
	
	char	*no;
	char	*so;
	char	*ea;
	char	*we;

	int		floor;
	int		ceiling;
	
} t_data;

typedef enum
{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	ARR_L = 123,
	ARR_R = 124,
}				keys;


#include "math.h"
#include <stdlib.h>

#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define MAP_SIZE 10
#define FOV M_PI / 3
#define RAY_STEP 0.01

typedef struct s_img_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img_data;

typedef struct t_txt_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;
} t_txt_data;

typedef struct s_player
{
	double x;
	double y;
	double dir;
} t_player;

typedef struct s_game
{
	void *mlx;
	void *win;
	t_player player;
	t_img_data img;
	//int map[MAP_SIZE][MAP_SIZE];

	t_txt_data textures[9]; //6 + 3
} t_game;

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

	t_txt_data *texture;
	int tex_x;
	
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


//-------------MAIN-----------------------//

//hook
int key_hook(int key, t_game *game);

void	routine(t_game *game);

//debug
void	print_stats(t_game *game);
void	print_textures(t_game *game);

int	game_loop(t_game *game);


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