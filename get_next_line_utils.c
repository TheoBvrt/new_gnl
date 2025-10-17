/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:24:40 by thbouver          #+#    #+#             */
/*   Updated: 2025/10/17 16:53:25 by thbouver         ###   ########.fr       */
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

void	*ft_calloc(size_t count, size_t size)
{
	void		*ptr;
	size_t		index;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	index = 0;
	while (index < count * size)
		((unsigned char *)ptr)[index ++] = '\0';
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

char	*ft_realloc(char *dest, char *src)
{
	char	*tmp;
	int		index;
	int		index_2;

	index = 0;
	index_2 = 0;
	tmp = ft_strdup(dest);
	free (dest);
	dest = ft_calloc(ft_strlen(tmp) + ft_strlen(src) + 1, sizeof(char));
	if (!dest)
		return (NULL);
	while (tmp[index_2])
		dest[index ++] = tmp[index_2 ++];
	index_2 = 0;
	while (src[index_2])
		dest[index ++] = src[index_2 ++];
	free (tmp);
	return (dest);
}
