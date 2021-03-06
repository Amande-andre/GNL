/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmande <anmande@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 22:54:50 by anmande           #+#    #+#             */
/*   Updated: 2022/07/22 05:34:01 by anmande          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = s;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return (s);
}

char	*ft_strdup(const char *s)
{
	char	*cpy;

	if (s == NULL)
		return (NULL);
	cpy = (char *)malloc((ft_strlen(s) + 1));
	if (cpy == NULL)
		return (NULL);
	if (cpy)
		ft_memcpy(cpy, s, (ft_strlen(s) + 1));
	return (cpy);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*s;
	char	*d;

	i = 0;
	s = (void *)src;
	d = dest;
	if (dest == NULL)
		return (NULL);
	if (src == NULL)
		return (NULL);
	while (i < n && src)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*s;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	s = (void *)malloc(sizeof(void) * (nmemb * size));
	if (!s)
		return (NULL);
	ft_memset(s, 0, size);
	return (s);
}