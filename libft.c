#include "libft.h"

void				ft_bzero(void *b, size_t n)
{
	unsigned char	*p;

	p = b;
	while (n > 0)
	{
		*p = 0;
		p++;
		n--;
	}
}

char		*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strnew(size_t size)
{
	char	*res;
	size_t	i;

	i = 0;
	res = (char *)malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i <= size)
	{
		res[i] = '\0';
		i++;
	}
	return (res);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;

	if (!s1)
		return (ft_strjoin("", s2));
	if (!s2)
		return (ft_strjoin(s1, ""));
	res = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (!res)
		return (NULL);
	ft_strcpy(res, s1);
	ft_strcpy(res + ft_strlen(s1), s2);
	return (res);
}