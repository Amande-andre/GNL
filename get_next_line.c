/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmande <anmande@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:04:05 by anmande           #+#    #+#             */
/*   Updated: 2022/08/02 05:46:53 by anmande          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	lens1;
	size_t	lens2;

	if (!s1)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	s = ft_calloc(sizeof(char), (lens1 + lens2) + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, s1, lens1);
	ft_memcpy(s + lens1, s2, lens2);
	s[ft_strlen(s)] = '\0';
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (str = ft_calloc(1, 1));
	else if (len > (unsigned int)ft_strlen(s) - start)
		str = ft_calloc(sizeof(char), (ft_strlen(s) - start) + 1);
	else
		str = ft_calloc(sizeof(char), (len) + 1);
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
	int				i;
	struct			s_data t_data;
	static	char 	*buff;
	
	t_data.line = NULL;
	//t_data.tmp = NULL;
	t_data.read_return = BUFFER_SIZE;
	i = 0;
	buff = malloc(BUFFER_SIZE + 1);
	while (t_data.read_return == BUFFER_SIZE)
	{
		if (buff[0] == 0)
		{
			t_data.read_return = read(fd, buff, BUFFER_SIZE);
			buff[t_data.read_return] = '\0';
		}
		while (buff[i] != '\0' && buff[i] != '\n')
			i++;
		if (buff)
		{
			t_data.tmp = ft_substr(buff, 0, i);
			t_data.line = ft_strjoin(t_data.line, buff);
			buff[0] = 0;
		}
		if (t_data.line == NULL)
		{
			t_data.line = ft_substr(buff, 0, i);
		}
		//ft_memset(buff, '\0', i);
		//buff = ft_strdup(ft_strchr(buff, '\n'));
		//rest = ft_strdup(ft_substr(buff, i + 1, BUFFER_SIZE - i));
	}
	return (t_data.line);
}

int	main(int ac, char **av)
{
	(void)ac;
	int i = atoi(av[1]);
	int fd = open("a_lire", O_RDONLY);
	char *fini;
	while (i > 0)
	{
		fini = get_next_line(fd);
		printf("%s", fini);
		free(fini);
		i--;
	}
	//printf("\n%d", fd);
	close(fd);
}
