/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmande <anmande@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:04:05 by anmande           #+#    #+#             */
/*   Updated: 2022/07/10 16:44:00 by anmande          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libget_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(char * buff);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dest, void *src, size_t n);
char	*ft_substr(char *s, unsigned int start, size_t len);

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t	i;
	char	*s;
	char	*d;

	i = 0;
	s = (void *)src;
	d = dest;
	if (dest == NULL)
		return (NULL);
	while (i < n && src)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(char *buff)
{
	int	i;
	while (buff[i])
		i++;
	return(i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	size_t	lens1;
	size_t	lens2;

	if (!s1)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	s = malloc(sizeof(char) * (lens1 + lens2) + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, s1, lens1);
	ft_memcpy(s + lens1, s2, lens2);
	s[ft_strlen(s)] = '\0';
	return (s);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (str = malloc(1 * 1));
	else if (len > (unsigned int)ft_strlen(s) - start)
		str = malloc(sizeof(char) * (ft_strlen(s) - start) + 1);
	else
		str = malloc(sizeof(char) * (len) + 1);
	if (!str)
		return (NULL);
	while (s[start] && i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	int					i;
	char				buff[BUFFER_SIZE + 1];
	static char			*rest;
	char				*line;
	static int			read_return;

	if (read_return)
		line = ft_strjoin(line, rest);
	rest = NULL;
	while (1)
	{
		i = 0;
		read_return = read(fd, buff, BUFFER_SIZE);
		if (read_return == 0)
			break;
		buff[BUFFER_SIZE] = '\0';
		// printf("%s", buff);
		while (buff[i] && buff[i] != '\n')
		{
			i++;
		}
		line = ft_strjoin(line, ft_substr(buff, 1, i - 1));
		if (buff[i] == '\n')
		{
			rest = buff + i;
			return (line);
		}
		else
			(rest = NULL);
	}
	return (line);
}

int	main(int ac, char **av)
{
	(void)ac;
	int i = atoi(av[1]);
	int fd = open("test", O_RDONLY);
	while (i-- > 0 )
	{
		printf("%s", get_next_line(fd));
		//i--;
	}
	
	//printf("\n%d", fd);
	close(fd);
}