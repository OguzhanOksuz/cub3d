/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 11:35:42 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/07 11:44:25 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	map_check(t_data *game, char *src)
{
	int	fd;

	fd = open(src, O_RDONLY);
	if (fd < 0)
		ft_error(ERR_FILE, game);

}
