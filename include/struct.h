/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:14:38 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/07 11:13:38 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/** Parser Struct
* @dir:		player's direction as an enum
* @x, @y:	player's coordinates
*
*/
typedef struct s_data
{
	char	**file;
	char	**map;
	char	*tmp;

	int		map_width;
	int		map_height;

	int		dir;

	int		x;
	int		y;

	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*f;
	char	*c;

	int		floor;
	int		ceiling;
}	t_data;

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

/** Texture Struct
 * Represents the details and content of a texture used in the game.
 *
 * @img:			A pointer representing the image of the texture.
 * 					Typically points to a data structure provided by the
 *                  graphics library, containing information about the image.
 *
 * @addr:			Pointer to the starting position of the
 * 					actual image data in memory.
 * 					Can be used for direct pixel manipulation.
 *
 * @bits_per_pixel:	Specifies the depth of the image. Determines
 * 					how many bits represent each pixel. 
 * 					Common values include 24 for RGB and 32 for RGBA
 *
 * @line_length:	The number of bytes to represent one horizontal line
 * 					of the image in memory.
 *					Useful for calculations when accessing pixels based on their x/y position.
 *
 * @endian:			Indicates the byte order format. Can be either
 * 					little endian or big endian.
 * 					This impacts how multi-byte numbers (like color values)
 * 					are stored in memory.
 *
 * @width, @height:	Dimensions of the texture in pixels. 
 *					Represents how wide (horizontal extent) and
 					tall (vertical extent) the texture is.
 */
typedef struct t_txt_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int		width;
	int		height;
}	t_txt_data;

/** Ray Struct
 * struct s_ray - Represents a ray for raycasting in a 2D world.
 *
 * @ray_dir:			Direction in which the ray is cast, represented as a vector.
 *						- x: horizontal component of the direction.
 *						- y: vertical component of the direction.
 *
 * @side_dist:			Distance the ray has to travel in the map grid to hit a side.
 *						- x: distance to the next side boundary along the x-axis.
 * 						- y: distance to the next side boundary along the y-axis.
 *
 * @delta_dist:			The length of the ray from one side to the next in the map grid
 *						- x: length along the x-axis.
 * 						- y: length along the y-axis.
 *
 * @map_x, @map_y:		The map grid indices (or coordinates) the ray is
 * 						currently inspecting.
 *
 * @perp_wall_dist:		Perpendicular distance from the player's position to the
 * 						wall hit by the ray.
 *
 * @step_x, @step_y:	The step direction for the ray in the map grid.
 * 						It can be either 1 (forward) or -1 (backward).
 *
 * @side:				Indicates which side of a grid box the ray hit.
 *						- 0: indicates a hit on the East-West wall.
 *						- 1: indicates a hit on the North-South wall.
 *
 * @hit:				Flag to indicate if the ray has hit a wall.
 * 						- 0: hit
 *						- 1: hasn't hit
 *
 * @texture:			Pointer to texture data that is mapped to the
 * 						wall hit by this ray.
 *
 * @tex_x:				The x-coordinate in the texture from which the pixel
 * 						should be drawn.
 *						It can be thought of as the exact horizontal position of the hit
 						in the texture.
 */
typedef struct s_ray
{
	t_point		ray_dir;
	t_point		side_dist;
	t_point		delta_dist;

	int			map_x;
	int			map_y;

	double		perp_wall_dist;

	int			step_x;
	int			step_y;

	int			side;
	int			hit;

	t_txt_data	*texture;
	int			tex_x;
}			t_ray;

/** Player Struct
 * 
 * @x:			last pressed key
 * @y:			img put results of raycasting and display
 * @dir			parsed data
 */
typedef struct s_player
{
	double	x;
	double	y;
	double	dir;

	double	dir_x;
	double	dir_y;
}	t_player;

/** Main Struct
 * 
 * @debug:			flag to show debug overlay
 * @key:			last pressed key
 * @img:			img to put results of raycasting and display
 * @data:			parsed data
 * @mapsize:		size of map
 * @textures:		(textures + minimap) 6 + 3
 */
typedef struct s_game
{
	void		*mlx;
	void		*win;

	int			debug;
	t_player	player;

	int			key;

	t_txt_data	img;

	t_data		*data;

	int			map_size;

	t_txt_data	textures[9];
}	t_game;
#endif