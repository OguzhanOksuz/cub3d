/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:13:49 by mkaraden          #+#    #+#             */
/*   Updated: 2023/07/05 17:35:04 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_filecheck(int ac, char **av)
{
	if (ac != 2)
		ft_error(ERROR_AC);
	if (!is_cub(av[1]))
		ft_error(ERROR_FILE);
	process_file(av[1]);
	if (!is_valid_char())
		ft_error(ERROR_CHAR);
	if (!is_walls_ok())
		ft_error(ERROR_WALLS);
	
}

int	is_cub(char *str)
{
	int	len;
	int	fd;

	fd = open(str, O_RDWR);
	if (!fd)
		return (0);
	len = ft_strlen(str);
	len--;
	if (str[len - 2] == 'c' && str[len - 1] == 'u' && str[len] == 'b')
	{
		if (str[len - 3] == '.' && str[len - 4] != '\0')
			return (1);
	}
	close(fd);
	return (0);
}