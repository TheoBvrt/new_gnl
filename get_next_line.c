/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:24:48 by thbouver          #+#    #+#             */
/*   Updated: 2025/10/09 13:59:22 by thbouver         ###   ########.fr       */
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

void	_get_line_from_cache(char **cache, char **dest)
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
	if ((*cache)[index] == '\n')
		_cache_line[cache_index] = (*cache)[index ++];
	cache_index = 0;
	while ((*cache)[index])
		_new_cache[cache_index ++] = (*cache)[index ++];
	free (*cache);
	*cache = _new_cache;
	*dest = _cache_line;
}

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

char	*ft_exit(char **cache, char *buffer)
{
	free (*cache);
	*cache = NULL;
	free (buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*buffer;
	char		*line;
	int			count;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!cache)
		cache = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer || !cache)
		return (NULL);
	if (ft_strchr(cache, '\n'))
		_get_line_from_cache(&cache, &line);
	else
	{
		line = NULL;
		count = read(fd, buffer, BUFFER_SIZE);
		if ((count == 0 && ft_strlen(cache) == 0))
			return (ft_exit(&cache, buffer));
		if (ft_strlen(cache) > 0)
			_get_line_from_cache(&cache, &line);
		line = ft_realloc(line, buffer);
		while (count != 0 && !ft_strchr(buffer, '\n'))
		{
			ft_bzero(buffer, BUFFER_SIZE + 1);
			count = read(fd, buffer, BUFFER_SIZE);
			line = ft_realloc(line, buffer);
		}
		trim_and_save(line, cache);
	}
	free (buffer);
	return (line);
}

// int	main(void)
// {
// 	int fd = open("testfile.txt", O_RDONLY);
// 	// char *line = get_next_line(fd);
// 	char *line;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free (line);
// 	}

	
// 	// char *line1 = get_next_line(fd);
// 	// printf ("-------------\n%s", line1);
// 	// free (line1);

// 	// char *line2 = get_next_line(fd);
// 	// printf ("%s\n", line2);
// 	// free (line2);

// 	// char *line3 = get_next_line(fd);
// 	// printf ("%s\n", line3);
// 	// free (line3);


// 	// get_next_line(fd);
// 	// get_next_line(fd);
// 	// get_next_line(fd);

// 	close (fd);
// }