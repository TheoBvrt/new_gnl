/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:24:48 by thbouver          #+#    #+#             */
/*   Updated: 2025/10/08 17:47:11 by thbouver         ###   ########.fr       */
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

void	ft_pustr(char *str)
{
	while (*str)
		write (1, str++, 1);
}

void	add_newline(char *src)
{
	int	index;

	index = 0;
	while (src[index])
		index ++;
	src[index] = '\n';
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*buffer;
	char		*line;
	char		*tmp;
	int			count;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!cache)
		cache = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer || !cache)
		return (NULL);
	if (ft_strchr(cache, '\n'))
	{
		printf("ici");
		line = _get_line_from_cache(&cache);
		add_newline(line);
	}
	else
	{
		tmp = ft_calloc(1, sizeof(char));
		if (!tmp)
			return(NULL);
		count = read(fd, buffer, BUFFER_SIZE);
		if ((count == 0 && ft_strlen(cache) == 0))
		{
			free (cache);
			free (buffer);
			free (tmp);
			return (NULL);
		}
		if (ft_strlen(cache) > 0)
		{
			free (tmp);
			tmp = _get_line_from_cache(&cache);
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
			trim_and_save(line, cache);
		free (tmp);
	}
	free (buffer);
	return (line);
}

int	main(void)
{
	int fd = open("testfile.txt", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free (line);
	}

	
	// char *line1 = get_next_line(fd);
	// printf ("-------------\n%s", line1);
	// free (line1);

	// char *line2 = get_next_line(fd);
	// printf ("%s\n", line2);
	// free (line2);

	// char *line3 = get_next_line(fd);
	// printf ("%s\n", line3);
	// free (line3);


	// get_next_line(fd);
	// get_next_line(fd);
	// get_next_line(fd);

	close (fd);
}