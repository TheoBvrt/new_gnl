/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:24:48 by thbouver          #+#    #+#             */
/*   Updated: 2025/10/07 17:27:34 by thbouver         ###   ########.fr       */
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

char	*_get_line_from_cache(char **cache)
{
	char	*_cache_line;
	char	*_new_cache;
	int		cache_index;
	int		index;
	
	cache_index = 0;
	index = 0;
	_new_cache = ft_calloc(ft_strlen(*cache) + 1, sizeof(char));
	_cache_line = ft_calloc(ft_strlen(*cache) + 1, sizeof(char));
	while ((*cache)[index] && (*cache)[index] != '\n')
		_cache_line[cache_index ++] = (*cache)[index ++];
	index ++;
	cache_index = 0;
	while ((*cache)[index])
		_new_cache[cache_index ++] = (*cache)[index ++];
	free (*cache);
	*cache = _new_cache;
	return (_cache_line);
}

void	trim_and_save(char *line, char *cache)
{
	int	index;
	int	index_cache;

	index = 0;
	index_cache = 0;
	while (line[index] != '\n')
			index ++;
		index ++;
	while (line[index])
	{
		cache[index_cache ++] = line[index];
		line[index ++] = '\0';
	}
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*buffer;
	char		*line;
	char		*tmp;
	int			count;

	if (fd == -1)
		return (NULL);
	tmp = ft_calloc(1, sizeof(char));
	if (!tmp)
		return(NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!cache)
		cache = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer || !cache)
		return (NULL);
	if (ft_strchr(cache, '\n'))
	{
		line = _get_line_from_cache(&cache);
		return (line);
	}
	else
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == 0 && ft_strlen(cache) == 0)
		{
			return (NULL);
		}
		if (ft_strlen(cache) > 0)
		{
			tmp = ft_strdup(cache);	
			ft_bzero(cache, BUFFER_SIZE + 1);
		}
		tmp = ft_realloc(tmp, buffer);
		while (count != 0 && !ft_strchr(buffer, '\n'))
		{
			ft_bzero(buffer, BUFFER_SIZE + 1);
			count = read(fd, buffer, BUFFER_SIZE);
			tmp = ft_realloc(tmp, buffer);
		}
		line = ft_strdup(tmp);
		if (ft_strchr(line, '\n'))
		{
			trim_and_save(line, cache);
		}
	}
	free (tmp);
	free (buffer);
	printf ("(%s)", line);
	return (line);
}

int	main(void)
{
	int fd = open("testfile.txt", O_RDONLY);
	char *line = get_next_line(fd);
	free (line);

	line = get_next_line(fd);
	free (line);

	line = get_next_line(fd);
	free (line);


	line = get_next_line(fd);
	free (line);
	close (fd);
}