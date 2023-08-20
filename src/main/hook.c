/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:51:01 by mkaraden          #+#    #+#             */
/*   Updated: 2023/08/20 15:24:30 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char* dtoa(double value);

int key_hook(int key, t_game *game)
{
	printf("KEY: %d\n", key);
	if (key == 53) // Escape key
		exit(0);
	double dir_x = cos(game->player.dir);
	double dir_y = sin(game->player.dir);
	double speed = 0.15;
	if (key == KEY_W)
	{
		game->player.x += dir_x * speed;
		game->player.y += dir_y * speed;
	}
	else if (key == KEY_S)
	{
		game->player.x -= dir_x * speed;
		game->player.y -= dir_y * speed;
	}
	else if (key == KEY_A) 
	{
		game->player.x += dir_y * speed;
		game->player.y -= dir_x * speed;
	}
	else if (key == KEY_D) 
	{
		game->player.x -= dir_y * speed;
		game->player.y += dir_x * speed;
	}
	else if (key == ARR_L)
	{
		game->player.dir -= 0.1;
		if (game->player.dir < 0) // Keep the angle between 0 and 2π
			game->player.dir += 2 * M_PI;
	}
	else if (key == ARR_R)
	{
		game->player.dir += 0.1;
		if (game->player.dir > 2 * M_PI) // Keep the angle between 0 and 2π
			game->player.dir -= 2 * M_PI;
	}
	
	//print_stats(game);
	routine(game);
	print_stats(game);
	//print_textures(game);

	return (0);
}

int key_hook2(int key, t_game *game)
{
	printf("KEY: %d\n", key);
	if (key == 53) // Escape key
		exit(0);
	double dir_x = cos(game->player.dir);
	double dir_y = sin(game->player.dir);
	double speed = 0.15;
	double new_x, new_y;
	if (key == KEY_W) // W
	{
		new_x = game->player.x + dir_x * speed;
		new_y = game->player.y + dir_y * speed;
		if(map[(int)new_y][(int)new_x] == 0)
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	else if (key == KEY_S) // S
	{
		new_x = game->player.x - dir_x * speed;
		new_y = game->player.y - dir_y * speed;
		if(map[(int)new_y][(int)new_x] == 0)
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	else if (key == KEY_A) // A
	{
		new_x = game->player.x + dir_y * speed;
		new_y = game->player.y - dir_x * speed;
		if(map[(int)new_y][(int)new_x] == 0)
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	else if (key == KEY_D) // D
	{
		new_x = game->player.x - dir_y * speed;
		new_y = game->player.y + dir_x * speed;
		if(map[(int)new_y][(int)new_x] == 0)
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	else if (key == ARR_L) // Left arrow key
	{
		game->player.dir -= 0.1;
		if (game->player.dir < 0) // Keep the angle between 0 and 2π
			game->player.dir += 2 * M_PI;
	}
	else if (key == ARR_R) // Right arrow key
	{
		game->player.dir += 0.1;
		if (game->player.dir > 2 * M_PI) // Keep the angle between 0 and 2π
			game->player.dir -= 2 * M_PI;
	}
	
	
	routine(game);
	print_stats(game);
	print_textures(game);

	return (0);
}

void	routine(t_game *game)
{
	//mlx_clear_window(game->mlx, game->win);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	draw_minimap(game);
}

void	print_stats(t_game *game)
{
	printf("\n\n--OMG Stats--\n\n");
	printf("dir = %f\n", game->player.dir);
	printf("\n-----XYZ------\n");
	printf("dir_x = %f\n", cos(game->player.dir));
	printf("dir_y = %f\n", sin(game->player.dir));
	printf("\n-----PPlayer------\n");
	printf("player_x = %f\n", game->player.x);
	printf("player_y = %f\n", game->player.y);

	int x = 700;
	int y = 10;
	mlx_string_put(game->mlx, game->win, x, y, RED, "dir: ");
	mlx_string_put(game->mlx, game->win, x, y + 10, RED, dtoa(game->player.dir));

	mlx_string_put(game->mlx, game->win, x, y + 30, RED, "dir_x: ");
	mlx_string_put(game->mlx, game->win, x, y + 40, RED, dtoa(cos(game->player.dir)));

	mlx_string_put(game->mlx, game->win, x, y + 60, RED, "dir_y: ");
	mlx_string_put(game->mlx, game->win, x, y + 70, RED, dtoa(sin(game->player.dir)));

	mlx_string_put(game->mlx, game->win, x, y + 90, RED, "player_x: ");
	mlx_string_put(game->mlx, game->win, x, y + 100, RED, dtoa(game->player.x));

	mlx_string_put(game->mlx, game->win, x, y + 120, RED, "player_y: ");
	mlx_string_put(game->mlx, game->win, x, y + 130, RED, dtoa(game->player.y));
}

void	print_textures(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->textures[NORTH].img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures[SOUTH].img, 64, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures[EAST].img, 128, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures[WEST].img, 192, 0);
}


#define DECIMAL_PLACES 4
#define MULTIPLIER 10000  // 10 raised to the power of DECIMAL_PLACES

char* dtoa(double value)
{
    char buffer[40];  // Local buffer to store the number.
    char* result;
    int i = 0, j = 0;
    int is_negative = 0;

    // Handle negative numbers.
    if (value < 0.0) {
        is_negative = 1;
        value = -value;
    }

    // Separate the integer and fractional parts of the double.
    int integer_part = (int)value;
    int decimal_part = (int)((value - integer_part) * MULTIPLIER + 0.5); // Adding 0.5 for rounding.

    // Convert the integer part to string.
    do {
        buffer[i++] = (integer_part % 10) + '0';
        integer_part /= 10;
    } while (integer_part);

    // Add negative sign for negative numbers.
    if (is_negative) {
        buffer[i++] = '-';
    }

    // Null terminate and reverse the integer part of the string.
    buffer[i] = '\0';
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }

    // Store the reversed string's length.
    int integer_length = i;

    // Append the decimal point.
    buffer[i++] = '.';

    // Convert the decimal part to string.
    for (int count = 0; count < DECIMAL_PLACES; count++) {
        buffer[i++] = (decimal_part % 10) + '0';
        decimal_part /= 10;
    }

    // Null terminate and reverse only the decimal part.
    buffer[i] = '\0';
    start = integer_length + 1;  // Start just after the '.'
    end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }

    // Allocate memory for result and copy from buffer.
    result = (char*)malloc((i + 1) * sizeof(char));
    if (!result) {
        // Memory allocation failed.
        return NULL;
    }

    while (buffer[j]) {
        result[j] = buffer[j];
        j++;
    }
    result[j] = '\0';

    return result;
}