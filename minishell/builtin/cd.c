#include "../minishell.h"
/*This code is a function for the built-in command "cd" in a shell. 
It takes in an array of strings (input) as an argument. 
The function first checks if the input has a second argument (input[1]). 
If it does, it attempts to change the current directory to the one specified by input[1].
If it fails, it prints an error message. If there is no second argument, 
the function looks for the environment variable "HOME" and attempts to 
change the current directory to that path. If it fails, it prints an error message. 
Finally, if this is not a parent process, the function exits with g_ms.

*/
void	builtin_cd(char **input)
{
	char	*home;

	if (input[1] != NULL)
	{
		if (chdir(input[1]) != 0)
			perror("minishell ");
	}
	else
	{
		home = getenv("HOME");
		if (home && *home)
			if (chdir(home))
				perror("minishell ");
	}
	if (!is_parent())
		exit (g_ms.exit_code);
}
