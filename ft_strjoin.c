#include "pipex.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*arr;
	int		size;
	int		i;

	if (!s1 && !s2)
		error(1, 0);
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(arr = (char *)malloc(size + 1)))
		error(0, 0);
	i = 0;
	while (*s1)
		arr[i++] = *s1++;
	while (*s2)
		arr[i++] = *s2++;
	arr[i] = 0;
	return (arr);
}
