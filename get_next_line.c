/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmande <anmande@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:04:05 by anmande           #+#    #+#             */
/*   Updated: 2022/06/28 07:46:03 by anmande          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libget_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


size_t	ft_strlen(char * buff);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);


size_t	ft_strlen(char *buff)
{
	int	i;
	while (buff[i])
		i++;
	return(i);
}

char	*ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	if (c > 256)
		c %= 256;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == c && c == '\0')
		return ((char *)s + i);
	return (NULL);
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

void	ft_putstr(char *buff)
{
	size_t	i;

	i = 0;
	while (buff[i])
	{
		//codition recursif si = \n pour recommencer le process
		if (buff == NULL || buff[0] == '\0')
			return;
		write(1, &buff[i], 1);
		i++;
	}
}

char	*get_next_line(int fd)
{
	int			i;
	char		buff[BUFFER_SIZE + 1];
	static char	*rest;
	char		*line;
	static int			read_return;

	if (read_return != 0)
		ft_putstr(rest);
	rest = NULL;
	while (1)
	{
		i = 0;
		read_return = read(fd, buff, BUFFER_SIZE);
		if (read_return == 0)
			break;
		buff[BUFFER_SIZE] = '\0';
		//printf("%s", buff);
		while (buff[i] && buff[i] != '\n')
		{
			write(1, &buff[i], 1);
			i++;
		}
		if (buff[i] == '\n')
		{
			//write(1, "\n", 1);
			rest = buff + i;
			return (rest);
		}
		else
			(rest = NULL);
	}
	return (rest);
}

int	main(int ac, char **av)
{
	(void)ac;
	int i = atoi(av[1]);
	int fd = open("a_lire", O_RDONLY);
	while (i > 0 )
	{
		get_next_line(fd);
		i--;
	}
	
	//printf("\n%d", fd);
	close(fd);
}