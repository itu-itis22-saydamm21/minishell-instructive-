#include "../minishell.h"
/*
This code is used to run a built-in command. 
It first duplicates the standard input and output streams (in and out) 
so that they can be restored later. Then, it gets all the inputs from the process, 
sets all the outputs for the process, runs the built-in command, 
and then restores the standard input and output streams. 
Finally, it closes both in and out.
*/
void	get_builtin(t_process *process)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	get_all_inputs(process);
	set_all_outputs(process);
	run_builtin(process->execute);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}
/*

This code is responsible for waiting for all the processes to finish before continuing. 
It starts by closing all file descriptors and 
then iterates through each process in the list of processes, 
checking if it has a valid PID. If it does, 
it waits for that process to finish and 
stores the exit code of that process in g_ms.exit_code. 
Finally, it sets the exit code to the status of the process before continuing.
*/
void	wait_cmd(void)
{
	t_process	*process;

	process = g_ms.process;
	close_all_fd();
	while (process)
	{
		if (process->pid != -1)
		{
			waitpid(process->pid, &g_ms.exit_code, 0);
			g_ms.exit_code = WEXITSTATUS(g_ms.exit_code);
			/*
			The waitpid() function takes three parameters: 
			the pid of the process to wait for, a pointer to an integer where 
			the exit code will be stored, and an optional flag that can be used to specify 
			how it should behave. 
			WEXITSTATUS() macro is then used to extract the exit status from the exit code 
			stored in g_ms.exit_code.*/
		}
		process = process->next;
	}
}
/*
It starts the command by filling in all the heredocs,
then checks if the command is a built-in and runs it if it is. 
If not, it runs each process one by one and waits for them to finish before exiting.
*/

void	start_cmd(void)
{
	t_process	*process;

	process = g_ms.process;
	if (!process)
		return ;
	fill_all_heredoc();
	if (g_ms.ignore)
		return (close_all_fd());
	if (is_builtin(process->execute[0]) && g_ms.process_count == 1)
	{
		get_builtin(process);
		process = process->next;
	}
	while (process)
	{
		run_cmd(process);
		process = process->next;
	}
	wait_cmd();
}
