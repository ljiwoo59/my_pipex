#include "pipex.h"

void error(int i)
{
	if (i == 1)
		write(1, "Error: Invalid Arguments\n", 25);
	else	
		perror("");
	exit(0);
}
