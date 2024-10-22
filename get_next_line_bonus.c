/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:09:35 by cschnath          #+#    #+#             */
/*   Updated: 2024/10/22 23:25:38 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=300 get_next_line_bonus.c get_next_line_utils_bonus.c
valgrind --leak-check=full ./a.out
*/

#include "get_next_line_bonus.h"

char	*ft_clean_buffer_bonus(char *buf)
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
	tmp = ft_calloc_b((ft_strlen_b(buf) - i + 1), sizeof(char));
	if (!tmp)
		return (NULL);
	i++;
	j = 0;
	while (buf[i])
		tmp[j++] = buf[i++];
	free(buf);
	return (tmp);
}

char	*ft_second_function_bonus(char *buf)
{
	int		j;
	char	*tmp;

	j = 0;
	if (!buf[j])
		return (NULL);
	while (buf[j] && buf[j] != '\n')
		j++;
	tmp = ft_calloc_b((j + 2), sizeof(char));
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

char	*ft_read_file_bonus(int fd, char *buf)
{
	char	*tmp;
	int		i;

	tmp = ft_calloc_b((BUFFER_SIZE + 2), sizeof(char));
	if (!tmp)
		return (NULL);
	i = 1;
	while (!(ft_strchr_b(buf, '\n')) && i != 0)
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (i == -1)
		{
			if (buf != NULL)
				free(buf);
			return (free(tmp), NULL);
		}
		tmp[i] = '\0';
		buf = ft_strjoin_b(buf, tmp);
	}
	free(tmp);
	return (buf);
}

char	*get_next_line_bonus(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_read_file_bonus(fd, buf);
	if (!buf)
		return (NULL);
	line = ft_second_function_bonus(buf);
	buf = ft_clean_buffer_bonus(buf);
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
	while ((next_line = get_next_line_bonus(fd)) != NULL)
	{
		printf("Line %d: %s", ++line_count, next_line);
		free(next_line);
	}
	return (0);
}
*/