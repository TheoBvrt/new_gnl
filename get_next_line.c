/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:24:48 by thbouver          #+#    #+#             */
/*   Updated: 2025/10/09 16:27:17 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	trim_and_save(char *line, char *cache)
{
	int	index;
	int	index_cache;

	index = 0;
	index_cache = 0;
	if (!ft_strchr(line, '\n'))
		return ;
	while (line[index] != '\n')
		index ++;
	index ++;
	while (line[index])
	{
		cache[index_cache ++] = line[index];
		line[index ++] = '\0';
	}
}

char	*ft_exit(char **cache, char *buffer, int free_cache, char *return_ptr)
{
	if (free_cache)
	{
		free (*cache);
		*cache = NULL;
	}
	free (buffer);
	return (return_ptr);
}

int	ft_init(char **buffer, char **cache, char **line, int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
		return (0);
	*buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!*cache)
		*cache = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!*buffer || !*cache)
		return (0);
	*line = NULL;
	return (1);
}

int	get_line_from_cache(char **cache, char **dest, int complete)
{
	char	*cache_line;
	char	*new_cache;
	int		cache_index;
	int		index;

	cache_index = 0;
	index = 0;
	if ((complete == 1 && !ft_strchr(*cache, '\n'))
		|| (complete == 0 && !(ft_strlen(*cache) > 0)))
		return (0);
	new_cache = ft_calloc(ft_strlen(*cache) + 1, sizeof(char));
	cache_line = ft_calloc(ft_strlen(*cache) + 1, sizeof(char));
	if (!new_cache || !cache_line)
		return (0);
	while ((*cache)[index] && (*cache)[index] != '\n')
		cache_line[cache_index ++] = (*cache)[index ++];
	if ((*cache)[index] == '\n')
		cache_line[cache_index] = (*cache)[index ++];
	cache_index = 0;
	while ((*cache)[index])
		new_cache[cache_index ++] = (*cache)[index ++];
	free (*cache);
	*cache = new_cache;
	*dest = cache_line;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*buffer;
	char		*line;
	int			info;

	if (!ft_init(&buffer, &cache, &line, fd))
		return (NULL);
	if (get_line_from_cache(&cache, &line, 1))
		return (ft_exit(&cache, buffer, 0, line));
	info = read(fd, buffer, BUFFER_SIZE);
	if ((info == 0 && ft_strlen(cache) == 0))
		return (ft_exit(&cache, buffer, 1, NULL));
	get_line_from_cache(&cache, &line, 0);
	line = ft_realloc(line, buffer);
	while (info != 0 && !ft_strchr(buffer, '\n'))
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		info = read(fd, buffer, BUFFER_SIZE);
		line = ft_realloc(line, buffer);
	}
	trim_and_save(line, cache);
	return (ft_exit(&cache, buffer, 0, line));
}
