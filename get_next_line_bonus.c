/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:09:35 by cschnath          #+#    #+#             */
/*   Updated: 2024/10/23 21:12:26 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
gcc -g -Wall -Werror -Wextra -D BUFFER_SIZE=300
get_next_line_bonus.c get_next_line_utils_bonus.c

valgrind --leak-check=full ./a.out
*/

#include "get_next_line_bonus.h"

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
		return (free(tmp), NULL);
	i++;
	j = 0;
	while (buf[i])
		tmp[j++] = buf[i++];
	tmp[j] = '\0';
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

	if (fd < 0)
		return (NULL);
	tmp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
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
	static char	*buf[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf[fd] = ft_read_file(fd, buf[fd]);
	if (!buf[fd])
		return (NULL);
	line = ft_second_function(buf[fd]);
	buf[fd] = ft_clean_buffer(buf[fd]);
	return (line);
}

int	main(void)
{
	int		fd1;
	int     fd2;
	int     fd3;
	char	*test1;
	char    *test2;
	char    *test3;
	int		line_count;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	line_count = 0;
	test1 = get_next_line(fd1);
	test2 = get_next_line(fd2);
	test3 = get_next_line(fd3);
	printf("Line %d: %s", ++line_count, test1);
	printf("Line %d: %s", ++line_count, test2);
	printf("Line %d: %s", ++line_count, test3);
	close(fd1);
	close(fd2);
	close(fd3);
	free(test1);
	free(test2);
	free(test3);
	return (0);
}
