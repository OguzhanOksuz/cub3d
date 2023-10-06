/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:58:09 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/07 00:37:52 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// void	ft_error(int err, void *ptr)
// {
// 	if (ptr)
// 		free(ptr);
// 	if (err == ERR_DEF)
// 		write(2, "An error accured", 17);
// 	else if (err == ERR_AC)
// 		write(2, "Invalid count of arguments", 27);
// 	else if (err == ERR_FILE)
// 		write(2, "Invalid file", 13);
// 	else if (err == ERR_CHAR)
// 		write(2, "Invalid chracter at map", 24);
// 	else if (err == ERR_WALLS)
// 		write(2, "Map is not surrounded by walls", 31);
// 	else if (err == ERR_SPACE)
// 		write(2, "Space in map", 31);
// 	else if (err == ERR_ORDER)
// 		write(2, "Items are not in correct order", 31);
// 	else if (err == ERR_PATH)
// 		write(2, "Invalid image path", 19);
// 	else if (err == ERR_EXIT)
// 		write(1, "pressed esc", 12);
// 	free(ptr);
// 	system("leaks cub3d");
// 	exit(1);
// }
