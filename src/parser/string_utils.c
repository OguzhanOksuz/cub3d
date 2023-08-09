/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:22:11 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/09 19:07:59 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_substr(t_game *game, char *str, int len)
{
	char	*rt;
	int		i;

	i = -1;
	rt = (char *)malloc(sizeof(char) * (len + 1));
	if (!rt)
		data_error(ERR_MALLOC, game);
	while (++i <= len)
		rt[i] = str[i];
	rt[i] = 0;
	return (rt);
}

int	is_mapline(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\n' || line[i] == 0)
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!(line[i] == ' ' || line[i] == '1' || line[i] == '0'
				|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W'))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strrchr(char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	while (i >= 0 && str[i] != ch)
		i--;
	return (str + i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
