/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:31:16 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/03 16:31:32 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DECIMAL_PLACES 4
#define MULTIPLIER 10000  // 10 raised to the power of DECIMAL_PLACES

void	print_stat(t_game *game, char *msg, int y, char *num)
{
	mlx_string_put(game->mlx, game->win, 700, y, RED, msg);
	mlx_string_put(game->mlx, game->win, 700, y + 10, RED, num);
	free(num);
}

void	print_stats(t_game *game)
{
	int y;
	if (!(game->debug))
		return;
	printf("\n\n--OMG Stats--\n\n");
	printf("dir = %f\n", game->player.dir);
	printf("\n-----XYZ------\n");
	printf("dir_x = %f\n", cos(game->player.dir));
	printf("dir_y = %f\n", sin(game->player.dir));
	printf("\n-----PPlayer------\n");
	printf("player_x = %f\n", game->player.x);
	printf("player_y = %f\n", game->player.y);
	y = 10;
	print_stat(game, "dir: ", y, dtoa(game->player.dir));
	print_stat(game, "dir_x: ", y + 30, dtoa(cos(game->player.dir)));
	print_stat(game, "dir_y: ", y + 60, dtoa(sin(game->player.dir)));
	print_stat(game, "player_x: ", y + 90, dtoa(game->player.x));
	print_stat(game, "player_y: ", y + 120, dtoa(game->player.y));
}

void	print_textures(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->textures[NORTH].img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures[SOUTH].img, 64, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures[EAST].img, 128, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures[WEST].img, 192, 0);
}

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
