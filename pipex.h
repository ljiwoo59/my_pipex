#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <sys/errno.h>
# include <string.h>

typedef struct s_cmd
{
	char *cmd[5];
}	t_cmd;

void set_in(char *file1);
void set_out(char *file2);
void set_pipe(int *fildes, int fd);
void command(char *cmd);
int ft_wordcount(char *s, char c);
void ft_strcpy(char *arr, char *start, char *end);
char **ft_split(char *s, char c);
char *ft_strjoin(char *s1, char *s2);
int ft_strlen(char *s);
void error(int i, char *s);
char	*ft_lower(char *s);
char	*ft_strdup(char *s1, int size);

#endif
