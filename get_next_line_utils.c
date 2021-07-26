#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	len++;
	while (len--)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len1;
	size_t		len2;
	char		*ret;
	const char	*temp;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	temp = s1;
	if (!(ret = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (0);
	ft_memcpy(ret, s1, len1);
	ft_memcpy(ret + len1, s2, len2);
	ret[len1 + len2] = '\0';
	free((char *)temp);
	return (ret);
}

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	size_t	idx;
	char	*temp;

	s_len = ft_strlen(s);
	idx = 0;
	if (!(temp = (char *)malloc(sizeof(char) * (s_len + 1))))
		return (NULL);
	while (s[idx])
	{
		temp[idx] = s[idx];
		idx++;
	}
	temp[idx] = '\0';
	return (temp);
}
