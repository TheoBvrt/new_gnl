/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:24:40 by thbouver          #+#    #+#             */
/*   Updated: 2025/10/17 01:08:59 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(char *str, char c)
{
	int	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index])
	{
		if (str[index] == c)
			return (1);
		index ++;
	}
	return (0);
}

size_t	ft_strlen(const char *string)
{
	size_t	lenght;

	lenght = 0;
	if (!string)
		return (0);
	while (string[lenght])
		lenght ++;
	return (lenght);
}

void	ft_bzero(void *pointer, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
		((unsigned char *)pointer)[index ++] = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_strdup(const char *source)
{
	int		index;
	char	*ptr;

	index = 0;
	if (!source)
		return (NULL);
	ptr = ft_calloc(ft_strlen(source) + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (source[index])
	{
		ptr[index] = source[index];
		index ++;
	}
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		index;
	int		index_2;
	char	*ptr;

	index = 0;
	index_2 = 0;
	ptr = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[index_2])
		ptr[index ++] = s1[index_2 ++];
	index_2 = 0;
	while (s2[index_2])
		ptr[index ++] = s2[index_2 ++];
	return (ptr);
}

char	*ft_realloc(char *dest, char *src)
{
	char	*tmp;
	if (!src && !dest)
		return (NULL);
	if (!src)
		return (dest);
	if (!dest)
		return (ft_strdup(src));

	tmp = ft_strdup(dest);
	if (!tmp)
		return (NULL);
	free (dest);
	dest = ft_strjoin(tmp, src);
	free (tmp);
	return (dest);
}