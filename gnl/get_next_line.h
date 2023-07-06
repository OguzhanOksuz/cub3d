/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 23:06:38 by mkaraden          #+#    #+#             */
/*   Updated: 2023/02/18 21:06:43 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif

size_t	ft_strlen(char *str);
size_t	ft_strlcpy(char	*dst, char *src, size_t	dstsize);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_line(char *str);
char	*ft_str(char *str);

char	*get_next_line(int fd);
int		check_newline(char *ptr);

char	*ft_init_stash(int fd, char *buffer);
char	*ft_init_line(char *line, char *stash);
char	*ft_edit_stash(char *stash);
char	*ft_strdup(char *str);

#endif