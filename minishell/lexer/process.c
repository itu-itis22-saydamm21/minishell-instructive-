#include "../minishell.h"
/*
This code initializes a process. It creates a t_process structure and 
allocates memory for it. It then creates a pipe, sets the pid to -1, 
allocates memory for the execute and redirects fields, 
and sets the prev and next pointers to NULL. Finally, it returns the process.
*/
t_process	*init_process(void)
{
	t_process	*process;

	process = ft_calloc(sizeof(t_process), 1);
	pipe(process->fd);	//This code is used to create a pipe between 
						// the process file descriptor (fd)
						// and the standard input/output of the process. 
						// The pipe allows data to be transferred between the two locations, 
						// allowing for communication between the process and its environment.
	process->pid = -1;
	process->execute = ft_calloc(sizeof(char *), 1);
	process->redirects = ft_calloc(sizeof(char *), 1);
	process->prev = NULL;
	process->next = NULL;
	return (process);
}
/*
This code adds a new process to the end of a linked list of processes. 
The function takes in two arguments: 
a pointer to a pointer of type t_process (**process) and 
a pointer to type t_process (*new_process). It first checks if the linked list is empty, 
and if so, sets the pointer to the new process. If the linked list is not empty, 
it iterates through the list until it reaches the last element, 
then sets that element's next pointer to point to the new process and 
sets the new process's prev pointer to point back at the last element.

*/
void	process_addback(t_process **process, t_process *new_process)
{
	t_process	*i_process;

	i_process = *process;
	if (!(i_process))
		*process = new_process;
	else
	{
		while (i_process->next)
			i_process = i_process->next;
		i_process->next = new_process;
		new_process->prev = i_process;
	}
}
