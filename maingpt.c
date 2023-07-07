/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maingpt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:38:07 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/07 16:09:06 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
} Game;

int map[MAP_SIZE][MAP_SIZE] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

void my_mlx_pixel_put(img_data *data, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    {
        return;
    }
	char *dst;
	int offset = (y * data->line_length + x * (data->bits_per_pixel / 8));

	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

void draw_line(Game *game, int x, double height, int color)
{
	int start = (HEIGHT - height) / 2;
	int end = (HEIGHT + height) / 2;
	for (int y = start; y < end; y++)
		my_mlx_pixel_put(&game->img, x, y, color);
}

void clearimg(Game *game)
{
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			my_mlx_pixel_put(&game->img, i, j, 0x00000000);
		}
	}
}
void raycast(Game *game)
{
    clearimg(game);
    double angle_step = FOV / WIDTH; // ray count
    double angle = game->player.dir - FOV / 2;
    for (int x = 0; x < WIDTH; x++, angle += angle_step)
    {
        double dirX = cos(angle);
        double dirY = sin(angle);
        
        int mapX = (int)game->player.x;
        int mapY = (int)game->player.y;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / dirX);
        double deltaDistY = fabs(1 / dirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (dirX < 0)
        {
            stepX = -1;
            sideDistX = (game->player.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
        }

        if (dirY < 0)
        {
            stepY = -1;
            sideDistY = (game->player.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // add boundary checks here
            if (mapX < 0 || mapX >= MAP_SIZE || mapY < 0 || mapY >= MAP_SIZE) 
            {
                hit = 1;
            }
            else if (map[mapY][mapX] > 0) 
            {
                hit = 1;
            }
        }

        if (hit && side == 0)
            perpWallDist = (mapX - game->player.x + (1 - stepX) / 2) / dirX;
        else if (hit)
            perpWallDist = (mapY - game->player.y + (1 - stepY) / 2) / dirY;
        else
            perpWallDist = HEIGHT;

        // Correct the "fishbowl effect" by multiplying the wall distance by cos(player_dir - ray_dir)
        perpWallDist *= cos(game->player.dir - angle);
        
        int lineHeight = (int)(HEIGHT / perpWallDist);
        draw_line(game, x, lineHeight, 0x00FF0000);
    }
}

int update(Game *game);

int key_hook(int key, Game *game)
{
    printf("KEY: %d\n", key);
    if (key == 53) // Escape key
        exit(0);
    double dir_x = cos(game->player.dir);
    double dir_y = sin(game->player.dir);
    double speed = 0.1;
	printf("\n\n--OMG Stats--\n\n");
	printf("dir = %f\n", game->player.dir);
	printf("\n-----XYZ------\n");
	printf("dir_x = %f\n", dir_x);
	printf("cos = %f\n",cos(game->player.dir));
	printf("dir_y = %f\n", dir_y);
	printf("sin = %f\n",sin(game->player.dir));
	printf("\n-----PPlayer------\n");
	printf("player_x = %f\n", game->player.x);
	printf("player_y = %f\n", game->player.y);
    if (key == 13) // W
    {
        game->player.x += dir_x * speed;
        game->player.y += dir_y * speed;
    }
    else if (key == 1) // S
    {
        game->player.x -= dir_x * speed;
        game->player.y -= dir_y * speed;
    }
    else if (key == 0) // A
    {
        game->player.x += dir_y * speed;
        game->player.y -= dir_x * speed;
    }
    else if (key == 2) // D
    {
        game->player.x -= dir_y * speed;
        game->player.y += dir_x * speed;
    }
    else if (key == 123) // Left arrow key
    {
        game->player.dir -= 0.1;
        if (game->player.dir < 0) // Keep the angle between 0 and 2π
            game->player.dir += 2 * M_PI;
    }
    else if (key == 124) // Right arrow key
    {
        game->player.dir += 0.1;
        if (game->player.dir > 2 * M_PI) // Keep the angle between 0 and 2π
            game->player.dir -= 2 * M_PI;
    }
	printf("player_x = %f\n", game->player.x);
	printf("player_y = %f\n", game->player.y);
	
	mlx_clear_window(game->mlx, game->win);
	raycast(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);

    return (0);
}


int key_hookHit(int key, Game *game)
{
    printf("KEY: %d\n", key);
    if (key == 53) // Escape key
        exit(0);
    double dir_x = cos(game->player.dir);
    double dir_y = sin(game->player.dir);
    double speed = 0.1;

    double new_x, new_y;
    if (key == 13) // W
    {
        new_x = game->player.x + dir_x * speed;
        new_y = game->player.y + dir_y * speed;
    }
    else if (key == 1) // S
    {
        new_x = game->player.x - dir_x * speed;
        new_y = game->player.y - dir_y * speed;
    }
    else if (key == 0) // A
    {
        new_x = game->player.x + dir_y * speed;
        new_y = game->player.y - dir_x * speed;
    }
    else if (key == 2) // D
    {
        new_x = game->player.x - dir_y * speed;
        new_y = game->player.y + dir_x * speed;
    }
    else if (key == 123) // Left arrow key
    {
        game->player.dir -= 0.1;
        if (game->player.dir < 0) // Keep the angle between 0 and 2π
            game->player.dir += 2 * M_PI;
    }
    else if (key == 124) // Right arrow key
    {
        game->player.dir += 0.1;
        if (game->player.dir > 2 * M_PI) // Keep the angle between 0 and 2π
            game->player.dir -= 2 * M_PI;
    }

    // If the player's new position is not inside a wall and is within map bounds, allow the move
    if (new_x >= 0 && new_x < MAP_SIZE && new_y >= 0 && new_y < MAP_SIZE && map[(int)new_y][(int)new_x] == 0)
    {
        game->player.x = new_x;
        game->player.y = new_y;
    }

    mlx_clear_window(game->mlx, game->win);
    raycast(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);

    return (0);
}
int main(void)
{
	Game game;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Raycaster");
	game.player.x = 2;
	game.player.y = 2;
	game.player.dir = M_PI / 4;

	game.img.img = mlx_new_image(game.mlx, 800, 600);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length,
									  &game.img.endian);
	
	//mlx_loop_hook(game.mlx, update, &game);
	mlx_hook(game.win, 2, 0, key_hook, &game);
	raycast(&game);
	mlx_loop(game.mlx);
	return (0);
}


int update(Game *game)
{
	mlx_clear_window(game->mlx, game->win);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    raycast(game);
	return 0;
}

void raycast2(Game *game)
{
	clearimg(game);
	double angle_step = FOV / WIDTH; //ray count
	double angle = game->player.dir - FOV / 2;
	for (int x = 0; x < WIDTH; x++, angle += angle_step)
	{
		double ray_x = game->player.x;
		double ray_y = game->player.y;
		while (map[(int)ray_y][(int)ray_x] == 0) //game->map
		{
			ray_x += RAY_STEP * cos(angle);
			ray_y += RAY_STEP * sin(angle);
		}
		double dist = sqrt(pow(ray_x - game->player.x, 2) + pow(ray_y - game->player.y, 2));
		double corrected_dist = dist * cos(game->player.dir - angle);
		double wall_height = (1 / corrected_dist) * HEIGHT;
		draw_line(game, x, wall_height, 0x00FF0000);
	}
}

// for (int i = 0; i < MAP_SIZE; i++)
// 	{
// 		for (int j = 0; j < MAP_SIZE; j++)
// 		{
// 			if (i == 0 || j == 0 || i == MAP_SIZE - 1 || j == MAP_SIZE - 1)
// 				game.map[i][j] = 1; // wall
// 			else
// 				game.map[i][j] = 0; // empty space
// 		}
// 	}
