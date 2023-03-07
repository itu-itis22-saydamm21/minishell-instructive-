#include "minishell.h"

t_minishell	g_ms;

void	init_app(char **env)
{
	g_ms.exit_code = 0;
	g_ms.parent_pid = getpid();
	g_ms.paths = NULL;
	set_env(env);
	set_paths();
}
/*
This code is a function called main_continue that takes in a character pointer (string) 
as an argument. The function first checks if the input contains a pipe character 
using the ft_pipecheck function. If it does, it calls the init_shell function 
with the input as an argument. Lastly, it adds the input to the history 
using the add_history function.
*/
void	main_continue(char *input)
{
	if (ft_pipecheck(input))
		init_shell(input);
	add_history(input);
}

/*This code is the main function of a Minishell program. 
It initializes the application with the environment variables,
sets up two signal handlers for SIGQUIT and SIGINT, 
reads an input from the user using the readline function, 
checks if it is valid with ctrl_d, 
and then passes it to main_continue if it is valid. 
Finally, it frees the input and exits with the exit code 
stored in g_ms.*/

int	main(int ac, char **av, char **env)
{
	char	*input;

	init_app(env);
	while (ac && av)
	{
		g_ms.ignore = FALSE;
		signal(SIGQUIT, &ctrl_bs);
		signal(SIGINT, &ctrl_c);
		write(1, "\033[32m", 5);
		input = readline("minishell:");
		write(1, "\033[0m", 4);
		ctrl_d(input);
		if (g_ms.ignore)
		{
			free(input);
			input = malloc(1);
		}
		else if (*input && g_ms.ignore == FALSE)
			main_continue(input);
		free(input);
	}
	exit(g_ms.exit_code);
}
