/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooksuz <ooksuz@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:05:02 by ooksuz            #+#    #+#             */
/*   Updated: 2023/08/12 22:13:20 by ooksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_wordcount(const char *s, char sep)
{
	int	count;
	int	is_word;

	count = 0;
	is_word = 0;
	while (*s)
	{
		if (*s != sep && !is_word)
		{
			is_word = 1;
			count++;
		}
		else if (*s == sep && is_word)
			is_word = 0;
		s++;
	}
	return (count);
}

char	*ft_worddup(const char *s, char sep, t_game *game)
{
	int		len;
	char	*word;
	char	*start;

	while (*s && *s == sep)
		s++;
	start = (char *)s;
	while (*s && *s != sep)
		s++;
	len = s - start;
	word = (char *)malloc(len + 1);
	if (!word)
		data_error(ERR_MALLOC, game);;
	word[len] = '\0';
	while (len--)
		word[len] = start[len];
	return (word);
}

char	**ft_split(char *s, char sep, t_game *game)
{
	int		count;
	int		i;
	char	**split;

	count = ft_wordcount(s, sep);
	split = (char **)malloc((count + 1) * sizeof(char *));
	if (!split)
		data_error(ERR_MALLOC, game);
	i = 0;
	while (i < count)
	{
		split[i] = ft_worddup(s, sep, game);
		if (!split[i])
		{
			while (i--)
				free(split[i]);
			free(split);
			data_error(ERR_MALLOC, game);
		}
		while (*s && *s != sep)
			s++;
		i++;
	}
	split[count] = 0;
	return (split);
}
