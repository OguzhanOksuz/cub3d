/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:11:25 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/19 18:58:40 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

# define WIDTH 800
# define HEIGHT 600

# define FOV 1.047198 //M_PI / 3
# define RAY_STEP 0.01
# define ANGLE_STEP 0.001309  //FOV / WIDTH

# define MOVE_SPEED 0.03 //0.05 0.15
# define TURN_SPEED 0.03 //0.5 0.3

/*
*
	ERR_AC, //Arguman count
	ERR_EXT, //Extension .cub
	ERR_ELEM, //Element
	ERR_ORDER, //Map order
	ERR_CHAR, //invalid char exist or occurance
	ERR_WALL, //wall
	ERR_MALLOC, // MAlloc Error
	ERR_PATH, //File is not exist
	ERR_READ, //File is not readable
	ERR_DEF,
	ERR_EXIT

*/

//side icin koy
typedef enum s_side
{
	X_AXIS,
	Y_AXIS
	
} t_side;
typedef enum s_err //
{
	ERR_AC,
	ERR_EXT,
	ERR_ELEM,
	ERR_ORDER,
	ERR_CHAR,
	ERR_WALL,
	ERR_MALLOC,
	ERR_PATH,
	ERR_READ,
	ERR_DEF,
	ERR_EXIT
}				t_err;

//yone ve texture
typedef enum s_dir
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
}				t_dir;

//klavye tus
typedef enum s_keys
{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	ARR_L = 123,
	ARR_R = 124,
}				t_keys;

//tus yon
typedef enum s_keydir
{
	KEY_WEST = 13,
	KEY_LEFT = 0,
	KEY_SOUTH = 1,
	KEY_EAST = 2,
	ARR_LEFT = 123,
	ARR_RIGHT = 124,
}				t_keydir;

typedef enum e_color
{
	RED = 0x00FF0000,
	GREEN = 0x0000FF00,
	BLUE = 0x000000FF,
	YELLOW = 0x00FFFF00,
	CEILING_BLUE = 0x00AAAAFF,
	FLOOR_BROWN = 0x00660000
}	t_color;

#endif
