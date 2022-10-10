/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmande <anmande@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:04:05 by anmande           #+#    #+#             */
/*   Updated: 2022/10/10 19:19:29 by anmande          ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	size_t	lens1;
	size_t	lens2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	// if (s1 == NULL)
	// 	return (s2);
	if (s2 == NULL)
		return (s1);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	s = ft_calloc(sizeof(char), (lens1 + lens2) + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, s1, lens1);
	ft_memcpy(s + lens1, s2, lens2);
	s[ft_strlen(s)] = '\0';
	free (s1);
	return (s);
}

char	*ft_substrbuff(char *s, unsigned int start, size_t len)
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
	free (s);
	return (str);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
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
	t_data.read_return = BUFFER_SIZE;
	i = 0;
	if (buff)
	{
		while (buff[i] != '\n' && buff[i] != '\0')
		{
			i++;
			if (buff[i] == '\n')
			{
				t_data.tmp = ft_substr(buff, 0, i + 1);
				buff = ft_substrbuff(buff, i + 1, ft_strlen(buff));
				return (t_data.tmp);
			}
		}
	}
	t_data.line = ft_strjoin(t_data.line, buff);
	buff = ft_calloc(BUFFER_SIZE + 1, 1);
	while (t_data.read_return > 0 && ft_strchr(buff, '\n') == NULL)
	{
		t_data.read_return = read(fd, buff, BUFFER_SIZE);
		if (t_data.read_return <= 0)
			return free(buff), (NULL);
		i = 0;
		while (buff[i] != '\0' && buff[i] != '\n')
		{
			// printf("%d : %c \n", i, buff[i]);
			i++;
		}
		//printf("===i===%d\n", i);
		if (buff[i] == '\n')
			t_data.tmp = ft_substr(buff, 0, i + 1);
		else
			t_data.tmp = ft_substr(buff, 0, i );
		//printf("tmp===>%s\n", t_data.tmp);
		if (buff[i] == '\n' || t_data.read_return < BUFFER_SIZE)
		{
			t_data.line = ft_strjoin(t_data.line, t_data.tmp);
			buff = ft_substrbuff(buff, i + 1, ft_strlen(buff));
			return (t_data.line);
			free (t_data.tmp);
		}
		if (t_data.tmp && buff[i] != '\n')
		{
			t_data.line = ft_strjoin(t_data.line, t_data.tmp);
			free (t_data.tmp);
		}
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
		printf("GNL_START===>%s", fini);
		free(fini);
		i--;
	}
	//printf("\n%d", fd);
	close(fd);
}
