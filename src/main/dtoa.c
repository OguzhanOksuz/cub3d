/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:48:31 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/21 20:45:02 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <string.h>

#define DECIMAL_PLACES 4
#define MULTIPLIER 10000  // 10 raised to the power of DECIMAL_PLACES

char	*get_decimal(double value);
char	*rev_str(char *str, int len);
char	*get_integer(double value);

char	*dtoa(double value)
{
	char	*rt;
	char	*integer_part;
	char	*decimal_part;

	integer_part = get_integer(value);
	decimal_part = get_decimal(value);
	rt = ft_strjoin(integer_part, ".");
	rt = ft_strjoin(rt, decimal_part);
	free(decimal_part);
	return (rt);
}

char	*get_decimal(double value)
{
	int		i;
	int		decimal_part;
	char	buffer[DECIMAL_PLACES + 1];

	if (value < 0.0)
		value = -value;
	decimal_part = (int)((value - ((int)value)) * MULTIPLIER + 0.5);
	i = 0;
	while (i < DECIMAL_PLACES)
	{
		buffer[i++] = (decimal_part % 10) + '0';
		decimal_part /= 10;
	}
	buffer[i] = '\0';
	return (rev_str(buffer, i));
}

char	*rev_str(char *str, int len)
{
	int		i;
	char	*rt;

	rt = malloc(sizeof(char) * (len + 1));
	i = -1;
	while (++i < len)
		rt[i] = str[len - i - 1];
	rt[len] = '\0';
	return (rt);
}

char	*get_integer(double value)
{
	int		i;
	int		integer_part;
	int		is_negative;
	char	buffer[40];

	is_negative = 0;
	if (value < 0.0)
	{
		is_negative = 1;
		value = -value;
	}
	integer_part = (int)value;
	i = 0;
	if (integer_part == 0)
		buffer[i++] = '0';
	while (integer_part)
	{
		buffer[i++] = (integer_part % 10) + '0';
		integer_part /= 10;
	}
	if (is_negative)
		buffer[i++] = '-';
	buffer[i] = '\0';
	return (rev_str(buffer, i));
}
