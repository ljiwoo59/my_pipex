#include "pipex.h"

void set_in(char *file1)
{
	int fd;

	if ((fd = open(file1, O_RDONLY)) < 0)
		error(0);
	if (dup2(fd, STDIN_FILENO) < 0)
		error(0);
	close(fd);
}

void set_out(char *file2)
{
	int fd;

	if ((fd = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
		error(0);
	if (dup2(fd, STDOUT_FILENO) < 0)
		error(0);
	close(fd);
}

void set_pipe(int *fildes, int fd)
{
	if (dup2(fildes[fd], fd) < 0)
		error(0);
	close(fildes[0]);
	close(fildes[1]);
}

void command(char *cmd)
{
	t_cmd cmmd;
	char **cmd_arr;
	int i;

	cmd_arr = ft_split(cmd, ' ');
	cmmd.cmd[0] = ft_strjoin("/bin/", cmd_arr[0]);
	cmmd.cmd[1] = ft_strjoin("/usr/local/bin/", cmd_arr[0]);
	cmmd.cmd[2] = ft_strjoin("/usr/bin/", cmd_arr[0]);
	cmmd.cmd[3] = ft_strjoin("/usr/sbin/", cmd_arr[0]);
	cmmd.cmd[4] = ft_strjoin("/sbin/", cmd_arr[0]);
	i = 0;
	while (i < 5)
		execve(cmmd.cmd[i++], cmd_arr, 0);
	error(0);
}

int main(int argc, char *argv[])
{
	int pid;
	int status;
	int fildes[2];

	if (argc != 5)
		error(1);
	if (pipe(fildes) < 0)
		error(0);
	if ((pid = fork()) < 0)
		error(0);
	else if (pid == 0)
	{
		set_in(argv[1]);
		set_pipe(fildes, STDOUT_FILENO);
		command(argv[2]);
	}
	else
	{
		set_out(argv[4]);
		set_pipe(fildes, STDIN_FILENO);
		if (waitpid(pid, &status, 0) < 0)
			error(0);
		if (WIFEXITED(status) == 0)
			exit(1);
		command(argv[3]);
	}
	return (0);
}
