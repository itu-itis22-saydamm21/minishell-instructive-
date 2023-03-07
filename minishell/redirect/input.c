#include "../minishell.h"
/*                        
This code is opening a file and setting it as the standard input. 
The function open() takes two arguments, 
the first being the name of the file to be opened and 
the second being a flag indicating how the file should be opened. 
In this case, O_RDONLY indicates that the file is to be opened in read-only mode. 
If open() returns -1, then no_file_err() is called with the name of the file as an argument. 
If open() succeeds, then dup2() is called with two arguments: 
fd (the file descriptor returned by open()) and 
0 (which indicates that standard input should be set to fd). 
Finally, close() is called on fd to free up resources.*/
void	input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (no_file_err(file));
	dup2(fd, 0);
	close(fd);
}
