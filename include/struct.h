/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:14:38 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/03 17:02:24 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

//.cub data 
typedef struct s_data
{
	char	**file; //  -Ozi
	char	**map; //map
	char	*tmp; 

	int		map_width; //en son halinin uzunlugu genisligi
	int		map_height;
	
	int		dir; //direction enum dan ver

	int		x; //final;
	int		y; //final
	
	char	*no; //raw-
	char	*so; //raw-
	char	*ea; //raw-
	char	*we; //raw-
	char	*f; //raw-
	char	*c; //raw-
	

	int		floor; //t_color enum daki gibi ver colorlari //final
	int		ceiling; // final
	
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
	
	int		side; //0 east west //1 nort south
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
	
	double dir_x;
	double dir_y;
	double speed;
} t_player;

typedef struct s_game
{
	void *mlx;
	void *win;

	int debug;
	t_player player;

	int key;

	//img to put raycasting results
	t_img_data img;
	
	//int map[MAP_SIZE][MAP_SIZE];
	t_data *data;

	int	map_size;

	t_txt_data textures[9]; //6 + 3
} t_game;


#endif
