#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(char *buff)
{
	int	i;
	while (buff[i])
		i++;
	return(i);
}

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
	s[ft_strlen(s + 1)] = '\0';
	return (s);
}


#include <stdio.h>
int main()
{
	char *s1 = "ceci";
	char *s2 = "est un test";
	printf("%s", ft_strjoin(s1, s2));
}