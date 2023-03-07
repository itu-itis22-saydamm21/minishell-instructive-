#include "../minishell.h"
/*
This code is part of a shell program. 
It is responsible for closing file descriptors associated with the shell process. 

The first function, close_heredoc_fd(), checks if the process contains a heredoc 
(a type of input redirection) and if the heredoc file descriptor is greater than 2. 
If both conditions are true, it closes the heredoc file descriptor. 

The second function, close_all_fd(), iterates through all processes in the shell and 
calls close_heredoc_fd() on each one. 
It then checks if the process's fd[0] and fd[1] are greater than 2 and 
closes them if they are.
*/
void	close_heredoc_fd(t_process *process)
{
	if (contain_heredoc(process) && process->heredoc_fd[0] > 2)
		close(process->heredoc_fd[0]);
}

void	close_all_fd(void)
{
	t_process	*process;

	process = g_ms.process;
	while (process)
	{
		close_heredoc_fd(process);
		if (process->fd[0] > 2)
			close(process->fd[0]);
		if (process->fd[1] > 2)
			close(process->fd[1]);
		process = process->next;
	}
}
