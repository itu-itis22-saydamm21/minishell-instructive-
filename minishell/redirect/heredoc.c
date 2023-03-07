#include "../minishell.h"

void	close_heredoc(int sig)
{
	(void)sig;
	g_ms.ignore = TRUE;
	g_ms.exit_code = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	/*This code uses the ioctl function to insert a newline character into the 
	input queue of the terminal associated with standard input (STDIN_FILENO). 
	The TIOCSTI argument tells ioctl that it is inserting a character into the input queue.
	The "\n" argument is the character that is being inserted.*/
}

/*This code is part of a function called heredoc() 
which is used to read input from the user. 
The function takes two parameters, an integer pointer and a character pointer. 
It begins by closing the file descriptors if they have already been opened. 
It then creates a pipe and enters an infinite loop where it waits for user input. 
The user input is compared to the endline parameter, and if they match, the loop is broken.
If they do not match, the input is written to the pipe and the loop continues. 
Finally, once the loop has been broken, the file descriptor for writing is closed.*/
void	heredoc(int *fd, char *endline)
{
	char		*input;
	static int	start = 0;

	if (start)
	{
		start = 1;
		close(fd[0]);
		close(fd[1]);
	}
	if (pipe(fd) < 0)
		return (perror("minishell"));
	while (1)
	{
		signal(SIGINT, &close_heredoc);
		input = readline("heredoc>> ");
		if (!input || ft_strcmp(input, endline) || g_ms.ignore)
		{
			free(input);
			break ;
		}
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
	close(fd[1]);
}
