#include "../minishell.h"
/*The code checks if the process is the first in the pipeline (prev == NULL) or 
the last in the pipeline (next == NULL). 
If it is, it will duplicate either fd[1] or prev->fd[0] to standard output (1) or 
standard input (0), respectively. 
If it is neither, it will duplicate both prev->fd[0] to standard input and 
fd[1] to standard output. This allows data to be passed between processes in a pipeline.
*/
void	pipe_route(t_process *process)
{
	if (process->prev == NULL)
		dup2(process->fd[1], 1);
	else if (process->next == NULL)
		dup2(process->prev->fd[0], 0);
	else
	{
		dup2(process->prev->fd[0], 0);
		dup2(process->fd[1], 1);
	}
}
/*
This code is part of a function that handles heredocs (here documents) in a shell. 
The function takes a t_process struct as an argument. 
The first line of the code duplicates the file descriptor stored 
in the heredoc_fd[0] field of the t_process struct and 
assigns it to file descriptor 0 (standard input). 
The second line checks if there is a next process in the pipeline and 
if so, it duplicates the file descriptor stored in fd[1] field of the t_process struct and 
assigns it to file descriptor 1 (standard output).
*/

void	heredoc_route(t_process *process)
{
	dup2(process->heredoc_fd[0], 0);
	if (process->next != NULL)
		dup2(process->fd[1], 1);
}

/*
It is a function called cmd_route() which takes in a process (t_process) as an argument. 
The function first checks if the process count is greater than 1, 
indicating that there are multiple processes. 
If so, it checks if the process contains 
heredocs (documents that contain text to be read as input). 
If so, it calls the heredoc_route() function on the process. 
Otherwise, it calls the pipe_route() function on the process. 
After this, it gets all of the inputs for the process and sets all of its outputs. 
Finally, it closes all file descriptors associated with the process.
*/

void	cmd_route(t_process *process)
{
	if (g_ms.process_count > 1)
	{
		if (contain_heredoc(process))
			heredoc_route(process);
		else
			pipe_route(process);
	}
	get_all_inputs(process);
	set_all_outputs(process);
	close_all_fd();
}
/*This code creates a new process (using the fork() function) and 
sets up the environment for it. It then sets up signal handlers for SIGQUIT and SIGINT, 
and calls cmd_route(), run_builtin(), and get_path() functions. 
Finally, it executes the command using execve() and 
prints an error if the command is not found. If the execution is successful, 
it exits with the global exit code. 
The pid of the new process is stored in the process->pid variable.
*/

void	run_cmd(t_process *process)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == CHILD_PROCESS)
	{
		signal(SIGQUIT, SIG_DFL);	//This code sets the action taken 
									//when the SIGQUIT signal is received to 
									//the default action. 
									//The default action for SIGQUIT is 
									//to terminate the process and produce a core dump.


		signal(SIGINT, SIG_DFL);	//This code sets the default action for the 
									//SIGINT signal, which is sent 
									//when a user presses Ctrl+C. 
									//The default action is to terminate the program.
		cmd_route(process);
		run_builtin(process->execute);
		path = get_path(process->execute[0]);
		execve(path, process->execute, g_ms.env);
		command_err(process->execute[0]);
		exit(g_ms.exit_code);
	}
	else
		process->pid = pid;
}
