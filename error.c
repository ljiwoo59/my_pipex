#include "pipex.h"

char *ft_lower(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	       i++;
	}
	return (s);
}	

char *ft_strdup(char *s1, int size)
{
	char *s;
	int i;

	if (!(s = (char *)malloc(size + 1)))
		error(0, 0);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = 0;
	return (s);
}

void error(int i, char *s)
{
	char *new_s;

	if (i == 1)
		write(2, "invalid argument\n", 17);
	else if (i == 2)
	{
		write(2, "command not found: ", 19);
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	else if (i == 3)
	{
		write(2, "permission denied: ", 19);
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	else
	{
		new_s = ft_strdup(strerror(errno), ft_strlen(strerror(errno)));
		new_s = ft_lower(new_s);
		write(2, new_s, ft_strlen(new_s));
		write(2, ": ", 2);
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	exit(1);
}
