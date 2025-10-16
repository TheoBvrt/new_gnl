/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:24:40 by thbouver          #+#    #+#             */
/*   Updated: 2025/10/16 16:36:46 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_realloc(char *dest, char *src);
void	ft_bzero(void *pointer, size_t n);
void	*ft_calloc(size_t count, size_t size);
int     ft_strchr(char *str, char c);
size_t	ft_strlen(const char *string);
char	*ft_strdup(const char *source);

#endif