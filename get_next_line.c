/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:24:48 by thbouver          #+#    #+#             */
/*   Updated: 2025/10/03 18:01:19 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//#define BUFFER_SIZE 10

int	endof_line(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\n')
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

void	trim_str(char *src)
{
	int	index;

	index = 0;
	if (endof_line(src) != 1)
		return ;
	while (src[index] != '\n')
		index ++;
	index ++;
	while (src[index])
		src[index] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		tmp[BUFFER_SIZE + 1];
	char		*newline;
	int			count;

	save(tmp, buffer);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	newline = ft_strdup(tmp);
	count = read(fd, buffer, BUFFER_SIZE);
	newline = ft_realloc(newline, buffer);
	while (!endof_line(buffer) && count != 0)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free (newline);
			return (NULL);
		}
		newline = ft_realloc(newline, buffer);
	}
	trim_str(newline);
	return (newline);
}

// int	main(void)
// {
// 	int fd = open("testfile.txt", O_RDONLY);
// 	char *line = get_next_line(fd);
// 	printf("%s", line);
// 	free (line);

// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free (line);

// 		line = get_next_line(fd);
// 	printf("%s", line);
// 	free (line);
// 	close(fd);
// }