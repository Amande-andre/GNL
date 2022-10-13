/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmande <anmande@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:08:52 by anmande           #+#    #+#             */
/*   Updated: 2022/10/13 12:30:31 by anmande          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGET_NEXT_LINE_H
# define LIBGET_NEXT_LINE_H
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

typedef struct s_data
{
	char	*line;
	char	*tmp;
	char	*tmp2;
	int		read_return;
}	t_data;

size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dest, char *src, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
void	ft_newbuff(char *buff);
void	ft_line(char *line, char *buff);

#endif