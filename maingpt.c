/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maingpt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:38:07 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/06 19:01:09 by mkaraden         ###   ########.fr       */
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

	int map[MAP_SIZE][MAP_SIZE];

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
	// mlx_pixel_put(game->mlx, game->win, x, y, color);
}

void raycast(Game *game)
{
	double angle_step = FOV / WIDTH;
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

int update(Game *game);

int key_hook2(int key, Game *game)
{
	printf("KEY: %d\n", key);
	if (key == 53) // Escape key
		exit(0);
	if (key == 13) // W
	{
		game->player.x += cos(game->player.dir) * 0.1;
		game->player.y += sin(game->player.dir) * 0.1;
	}
	else if (key == 1) // S
	{
		game->player.x -= cos(game->player.dir) * 0.1;
		game->player.y -= sin(game->player.dir) * 0.1;
	}
	else if (key == 0) // A
	{
		game->player.x -= sin(game->player.dir) * 0.1;
		game->player.y += cos(game->player.dir) * 0.1;
	}
	else if (key == 2) // D
	{
		game->player.x += sin(game->player.dir) * 0.1;
		game->player.y -= cos(game->player.dir) * 0.1;
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
	mlx_clear_window(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	raycast(game);

	return (0);
}

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
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    raycast(game);

    return (0);
}



int update(Game *game)
{
	mlx_clear_window(game->mlx, game->win);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    raycast(game);
	return 0;
}

int main(void)
{
	//
	Game game;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Raycaster");
	game.player.x = 2;
	game.player.y = 2;
	game.player.dir = M_PI / 4;

	game.img.img = mlx_new_image(game.mlx, 800, 600);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length,
									  &game.img.endian);

	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if (i == 0 || j == 0 || i == MAP_SIZE - 1 || j == MAP_SIZE - 1)
				game.map[i][j] = 1; // wall
			else
				game.map[i][j] = 0; // empty space
		}
	}

	

	

	// mlx_expose_hook(game.win, expose_hook, &game);
	// mlx_loop_hook(game.mlx, expose_hook, &game);

	//mlx_loop_hook(game.mlx, update, &game);
	mlx_hook(game.win, 2, 0, key_hook, &game);
	raycast(&game);
	mlx_loop(game.mlx);
	return (0);
}
