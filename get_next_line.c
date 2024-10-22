/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 00:18:16 by cschnath          #+#    #+#             */
/*   Updated: 2024/10/22 23:02:40 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

Fd			Name				<unistd.h>			<stdio.h>
0		Standard Input		STDIN_FILENO	stdin
1		Standard Output    STDOUT_FILENO	stdout
2		Standard Error		STDERR_FILENO	stderr

gcc -Wall -Werror -Wextra -D BUFFER_SIZE=300 *.c
valgrind --leak-check=full ./a.out

Return 1 when a line has been read, 0 when EOF has been
reached, -1 when an error happened

*/

#include "get_next_line.h"

char	*ft_clean_buffer(char *buf)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	tmp = ft_calloc((ft_strlen(buf) - i + 1), sizeof(char));
	if (!tmp)
		return (NULL);
	i++;
	j = 0;
	while (buf[i])
		tmp[j++] = buf[i++];
	free(buf);
	return (tmp);
}

char	*ft_second_function(char *buf)
{
	int		j;
	char	*tmp;

	j = 0;
	if (!buf[j])
		return (NULL);
	while (buf[j] && buf[j] != '\n')
		j++;
	tmp = ft_calloc((j + 2), sizeof(char));
	if (!tmp)
		return (NULL);
	j = 0;
	while (buf[j] && buf[j] != '\n')
	{
		tmp[j] = buf[j];
		j++;
	}
	if (buf[j] == '\n')
	{
		tmp[j] = buf[j];
		j++;
	}
	return (tmp);
}

char	*ft_read_file(int fd, char *buf)
{
	char	*tmp;
	int		i;

	tmp = ft_calloc((BUFFER_SIZE + 2), sizeof(char));
	if (!tmp)
		return (NULL);
	i = 1;
	while (!(ft_strchr(buf, '\n')) && i != 0)
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (i == -1)
		{
			if (buf != NULL)
				free(buf);
			return (free(tmp), NULL);
		}
		tmp[i] = '\0';
		buf = ft_strjoin(buf, tmp);
	}
	free(tmp);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_read_file(fd, buf);
	if (!buf)
		return (NULL);
	line = ft_second_function(buf);
	buf = ft_clean_buffer(buf);
	if (!buf)
	{
		free(buf);
		buf = NULL;
	}
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*next_line;
	int		line_count;

	fd = open("test.txt", O_RDONLY);
	line_count = 0;
	while ((next_line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", ++line_count, next_line);
		free(next_line);
	}
	return (0);
}
*/