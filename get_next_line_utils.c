/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:24:51 by thbouver          #+#    #+#             */
/*   Updated: 2025/10/09 15:11:07 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (1);
		index ++;
	}
	return (0);
}

int	ft_strlen(const char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index ++;
	return (index);
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

char	*ft_realloc(char *dest, char *src)
{
	char	*new;
	int		index;
	int		ptr_index;

	index = 0;
	ptr_index = 0;
	if (dest)
		new = ft_calloc(ft_strlen(dest) + ft_strlen(src) + 1, sizeof(char));
	else
		new = ft_calloc(ft_strlen(src) + 1, sizeof(char));
	if (!new)
		return (NULL);
	if (dest)
	{
		while (dest[index])
			new[ptr_index ++] = dest[index ++];
		index = 0;
	}
	while (src[index])
		new[ptr_index ++] = src[index ++];
	free (dest);
	return (new);
}
