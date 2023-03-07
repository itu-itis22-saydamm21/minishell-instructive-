#include "../minishell.h"
/*This code is part of a shell program. 
It is a function that takes in a process structure as an argument. 
The function iterates through the redirects array of the process structure and 
checks if each element is an input operator or a here document operator. 
If it is an input operator, the function calls another function called input() and 
passes in the next element of the array as an argument. If it is a here document operator, 
it duplicates file descriptor 0 with the file descriptor stored 
in the heredoc_fd array of the process structure.
*/
void	get_all_inputs(t_process *process)
{
	int		i;
	char	**redirects;

	i = 0;
	redirects = process->redirects;
	while (redirects[i])
	{
		if (is_operator(redirects[i]) == RED_INPUT)
			input(redirects[i + 1]);
		else if (is_operator(redirects[i]) == HERE_DOC)
			dup2(process->heredoc_fd[0], 0);
		i += 2;
	}
}
/*This code is part of a function that sets all of the outputs for a process. 
It loops through the redirects array, which contains strings of operators and file names. 
The function checks if the operator is an output redirection operator (RED_OUTPUT) or 
an append redirection operator (RED_APP

*/
void	set_all_outputs(t_process *process)
{
	int		i;
	char	**redirects;

	i = 0;
	redirects = process->redirects;
	while (redirects[i])
	{
		if (is_operator(redirects[i]) == RED_OUTPUT)
			output(redirects[i + 1], REPLACE);
		else if (is_operator(redirects[i]) == RED_APPEND)
			output(redirects[i + 1], APPEND);
		i += 2;
	}
}
/*
 It is a function that fills all heredocs in the program. 
 A heredoc is a type of redirection that allows for input to be sent to the program 
 from standard input instead of from a file. 
 The function iterates through each process in the shell and 
 checks if there are any redirects with the operator "HERE_DOC". 
 If there are, it calls the heredoc() function with the file descriptor and 
 redirect as parameters.
*/
void	fill_all_heredoc(void)
{
	int			i;
	char		**redirects;
	t_process	*process;

	process = g_ms.process;
	while (process)
	{
		i = 0;
		redirects = process->redirects;
		while (redirects[i] && !(g_ms.ignore))
		{
			if (is_operator(redirects[i]) == HERE_DOC)
				heredoc(process->heredoc_fd, redirects[i + 1]);
			/*This code is used to redirect the output of a process to a file descriptor. 
			The heredoc_fd parameter is a file descriptor associated with the process, 
			and the redirects[i + 1] parameter is an array containing the destination 
			for the output. The code will take the output from the process and write it 
			to the specified destination.*/
			i += 2;
		}
		process = process->next;
	}
}
