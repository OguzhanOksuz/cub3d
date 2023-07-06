/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 23:06:34 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/18 21:06:28 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		return (NULL);
	}
	stash[fd] = ft_init_stash(fd, stash[fd]);
	if (!stash[fd] || ft_strlen(stash[fd]) < 1)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (stash[fd]);
	}
	line = ft_init_line(line, stash[fd]);
	stash[fd] = ft_edit_stash(stash[fd]);
	return (line);
}

char	*ft_init_stash(int fd, char *stash)
{
	char	*buffer;
	int		rd;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	rd = 1;
	while (!check_newline(stash) && rd)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
		{
			free(stash);
			stash = NULL;
			free(buffer);
			return (NULL);
		}
		buffer[rd] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*ft_init_line(char *line, char *stash)
{
	int	i;

	i = 0;
	if (!stash)
	{
		return (NULL);
	}
	line = malloc(sizeof(char) * (ft_strlen(stash) + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_edit_stash(char *stash)
{
	char	*new_stash;
	int		i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		i++;
	}
	if (stash[i] == '\n')
	{
		i++;
	}
	new_stash = ft_strdup(stash + i);
	if (!new_stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	free(stash);
	stash = NULL;
	return (new_stash);
}
