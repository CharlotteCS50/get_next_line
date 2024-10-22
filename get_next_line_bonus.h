/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:09:52 by cschnath          #+#    #+#             */
/*   Updated: 2024/10/22 23:12:40 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strjoin_b(char *s1, char *s2);
size_t	ft_strlen_b(char *s);
char	*ft_strchr_b(char *s, int c);
void	*ft_calloc_b(size_t count, size_t size);
char	*get_next_line_bonus(int fd);
char	*ft_clean_buffer_bonus(char *buf);
char	*ft_read_file_bonus(int fd, char *buf);
char	*ft_second_function_bonus(char *buf);

#endif
