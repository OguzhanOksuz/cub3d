/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:11:25 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/03 15:12:23 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H


#define WIDTH 800
#define HEIGHT 600
#define MAP_SIZE 10
#define FOV M_PI / 3
#define RAY_STEP 0.01
#define ANGLE_STEP FOV / WIDTH;

typedef enum s_err //
{
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
}				t_err; //def kalsin gerisini kafana gore koy


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
}				t_dir; //hem yon hem texture icin


typedef enum s_keys
{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	ARR_L = 123,
	ARR_R = 124,
}				t_keys;

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
    RED = 0x00FF0000,      // Red for east
    GREEN = 0x0000FF00,    // Green for west
    BLUE = 0x000000FF,     // Blue for north
    YELLOW = 0x00FFFF00,   // Yellow for south
    CEILING_BLUE = 0x00AAAAFF, // Blueish color for the ceiling
    FLOOR_BROWN = 0x00660000   // Brownish color for the floor
	
} t_color;


#endif
