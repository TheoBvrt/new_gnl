/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:24:40 by thbouver          #+#    #+#             */
/*   Updated: 2025/10/17 16:26:22 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_exit(char **ptr1, char *return_ptr)
{
	free (*ptr1);
	*ptr1 = NULL;

	return (return_ptr);
}

char	*_get_line(char *cache)
{
	char	*line;
	int		index_a;

	index_a = 0;
	if (!cache)
		return (NULL);
	while (cache[index_a] && cache[index_a] != '\n')
		index_a ++;
	if (cache[index_a] == '\n')
		index_a ++;
	line = ft_calloc(index_a + 1, sizeof(char));
	if (!line)
		return (NULL);
	index_a = 0;
	while (cache[index_a] && cache[index_a] != '\n')
	{
		line[index_a] = cache[index_a];
		index_a ++;
	}
	if (cache[index_a] == '\n')
		line[index_a] = '\n';
	return (line);
}

char	*_update_cache(char *cache)
{
	char	*tmp;
	int		index_a;
	int		index_b;

	index_a = 0;
	index_b = 0;
	tmp = ft_strdup(cache);
	if (!tmp)
		return (NULL);
	free (cache);
	cache = ft_calloc(ft_strlen(tmp) + 1, sizeof(char));
	if (!cache)
		return (NULL);
	while (tmp[index_a] && tmp[index_a] != '\n')
		index_a ++;
	if (tmp[index_a] == '\n')
		index_a ++;
	while (tmp[index_a])
		cache[index_b++] = tmp[index_a++];
	free (tmp);
	return (cache);
}

char	*_read_file(char *buffer, int fd, char *stash)
{
	char	*cache;
	int		state;

	state = 1;
	cache = ft_calloc(1, sizeof(char));
	if (!cache)
		return (NULL);
	if (stash)
	{
		cache = ft_realloc(cache, stash);
		if (!cache)
			return (NULL);
		free (stash);
	}
	while (state > 0 && !ft_strchr(buffer, '\n'))
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		state = read(fd, buffer, BUFFER_SIZE);
		if (state == -1)
			return (free_exit(&cache, NULL));
		cache = ft_realloc(cache, buffer);
		if (!cache)
			return (NULL);
	}
	return (cache);	
}

char	*get_next_line(int fd)
{
	static char	*cache = NULL;
	char		*buffer;
	char		*line;
	
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_exit(&buffer, NULL));
	if (!ft_strchr(cache, '\n'))
	{
		cache = _read_file(buffer, fd, cache);
		if (!cache)
			return (free_exit(&buffer, NULL));
	}
	if (ft_strlen(cache) == 0)
	{
		free (cache);
		cache = NULL;
		free (buffer);
		return (NULL);
	}
	line = _get_line(cache);
	cache = _update_cache(cache);
	return (free_exit(&buffer, line));
}
