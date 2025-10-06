/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:24:48 by thbouver          #+#    #+#             */
/*   Updated: 2025/10/06 17:51:03 by thbouver         ###   ########.fr       */
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

void	save(char *dst, char *src)
{
	int	index;
	int	dest_index;

	index = 0;
	dest_index = 0;
	ft_bzero(dst, BUFFER_SIZE + 1);
	while (src[index] && src[index] != '\n')
		index ++;
	index ++;
	while (src[index])
		dst[dest_index ++] = src[index ++];
}

// void	trim_str(char *src)
// {
// 	int	index;

// 	index = 0;
// 	if (endof_line(src) != 1)
// 		return ;
// 	while (src[index] != '\n')
// 		index ++;
// 	index ++;
// 	while (src[index])
// 		src[index] = '\0';
// }

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

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*buffer;
	char		*line;
	char		*tmp;

	if (fd == -1)
		return (NULL);
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!cache)
		cache = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer || !cache)
		return (NULL);
	if (ft_strlen(cache) > 0)
		tmp = _get_line_from_cache(&cache);
	
	free (tmp);
	free (buffer);
	return (line);
}

int	main(void)
{
	int fd = open("testfile.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("%s", line);
}