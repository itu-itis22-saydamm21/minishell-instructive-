#include "../minishell.h"
/*This code opens a file in either replace or append mode, 
depending on the value of the 'mode' parameter. 
If the open fails, it prints an error message and either returns or exits, 
depending on whether it is in the parent process. 
Finally, it duplicates the file descriptor for the opened file and closes it.*/
void	output(char *file, int mode)
{
	int		fd;

	fd = 0;
	if (mode == REPLACE)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (mode == APPEND)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("minishell");
		if (is_parent())
			return ;
		else
			exit(g_ms.exit_code);
	}
	dup2(fd, 1);
	close(fd);
}
