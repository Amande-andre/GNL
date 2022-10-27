/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmande <anmande@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:04:05 by anmande           #+#    #+#             */
/*   Updated: 2022/10/25 15:31:17 by anmande          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	size_t	lens1;
	size_t	lens2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
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
	int	j;

	j = 0;
	ft_memset(line, '\0', BUFFER_SIZE + 1);
	while (buff[j] && buff[j - 1] != '\n')
	{
		line[j] = buff[j];
		j++;
	}
}

void	ft_newbuff(char *buff, int read)
{
	char	*tmpbuff;
	int		j;
	int		i;

	j = 0;
	i = 0;
	buff[read] = '\0';
	tmpbuff = ft_strdup(buff);
	while (buff[i] != '\n' && buff[i])
		i++;
	ft_memset(buff, '\0', BUFFER_SIZE);
	while (tmpbuff[i] != '\0')
	{
		i++;
		buff[j] = tmpbuff[i];
		j++;
	}
	buff[i] = '\0';
	free (tmpbuff);
}

char	*get_next_line(int fd)
{
	static char		buff[BUFFER_SIZE + 1];
	struct s_data	t_data;
	char			line[BUFFER_SIZE + 1];

	t_data.line = NULL;
	t_data.read_return = BUFFER_SIZE;
	ft_memset(line, '\0', BUFFER_SIZE + 1);
	ft_line(line, buff);
	t_data.line = ft_strjoin(t_data.line, line);
	while (t_data.read_return > 0 && ft_strchr(buff, '\n') == NULL)
	{
		t_data.read_return = read(fd, buff, BUFFER_SIZE);
		if ((buff[0] == '\0' && t_data.read_return <= 0)
			|| fd > 1024 || BUFFER_SIZE == 0)
		{
			free (t_data.line);
			return (NULL);
		}
		buff[t_data.read_return] = '\0';
		ft_line(line, buff);
		t_data.line = ft_strjoin(t_data.line, line);
	}
	ft_newbuff(buff, t_data.read_return);
	return (t_data.line);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	int i = atoi(av[1]);
// 	int j = 1;
// 	int fd = open("a_lire", O_RDONLY);
// 	char *fini;
// 	while (i > 0)
// 	{
// 		fini = get_next_line(fd);
// 		printf("GNL_START%d===>%s\n", j, fini);
// 		free(fini);
// 		i--;
// 		j++;
// 	}
// 	close(fd);
// 	return (0);
// }
