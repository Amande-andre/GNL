/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmande <anmande@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:04:05 by anmande           #+#    #+#             */
/*   Updated: 2022/10/13 18:19:01 by anmande          ###   ########.fr       */
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

char	*ft_strdup(const char *s)
{
	char	*cpy;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	cpy = (char *)malloc((ft_strlen(s)) + 1);
	if (cpy == NULL)
		return (NULL);
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	return (cpy);
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

void	ft_line(char *line, char *buff)
{
	int 	j;

	j = 0;
	while (buff[j] && buff[j] != '\n')
	{
		line[j] = buff[j];
		j++;
	}
	line[j] = '\0';
}

void	ft_newbuff(char *buff)
{
	char	*tmpbuff;
	int		j;
	int		i;

	j = 0;
	i = 0;
	tmpbuff = ft_strdup(buff);
	while (buff[i] != '\n' && buff[i])
		i++;
	while (tmpbuff[i])
	{
		i++;
		buff[j] = tmpbuff[i];
		j++;
	}
	free (tmpbuff);
}

char	*get_next_line(int fd)
{
	struct			s_data t_data;
	static	char 	buff[BUFFER_SIZE + 1];
	char			line[BUFFER_SIZE + 1];

	t_data.line = NULL;
	t_data.read_return = BUFFER_SIZE;
	while (t_data.read_return > 0 && ft_strchr(buff, '\n') == NULL)
	{
		t_data.read_return = read(fd, buff, BUFFER_SIZE);
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
		printf("GNL_START===>%s\n", fini);
		free(fini);
		i--;
	}
	//printf("\n%d", fd);
	close(fd);
}
