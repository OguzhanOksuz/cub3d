/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:58:09 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/19 18:11:31 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	ft_error(int err, void *ptr)
{
	if (ptr)
		free(ptr);
	if (err = ERR_DEF)
		write(2, "An error accured", 17);
	else if (err = ERR_AC)
		write(2, "Invalid count of arguments", 27);
	else if (err = ERR_FILE)
		write(2, "Invalid file", 13);
	else if (err = ERR_CHAR)
		write(2, "Invalid chracter at map", 24);
	else if (err = ERR_WALLS)
		write(2, "Map is not surrounded by walls", 31);
	else if (err = ERR_MAP)
		write(2, "Space in map", 31);
	else if (err = ERR_ORDER)
		write(2, "Items are not in correct order", 31);
	else if (err = ERR_PATH)
		write(2, "Invalid image path", 19);
	free(ptr);
	exit(1);
}