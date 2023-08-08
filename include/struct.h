/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:14:38 by mkaraden          #+#    #+#             */
/*   Updated: 2023/08/08 21:39:00 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

//.cub data 
typedef struct s_data
{
	char	**raw_map //  -Ozi
	char	**map; //map
	int		map_width; //en son halinin uzunlugu genisligi
	int		map_height;
	
	int		dir; //direction enum dan ver

	int		x;
	int		y;
	
	char	*no; //string
	char	*so; //
	char	*ea;
	char	*we;

	

	int		floor; //t_color enum daki gibi ver colorlari
	int		ceiling; //
	
} t_data;


//img 

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





//raycast

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



// game

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

	//img to put raycasting results
	t_img_data img;
	
	//int map[MAP_SIZE][MAP_SIZE];
	t_data *data;

	t_txt_data textures[9]; //6 + 3
} t_game;


#endif
