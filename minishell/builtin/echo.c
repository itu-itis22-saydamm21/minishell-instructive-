#include "../minishell.h"

void	put_str(char *str, int i)
{
	while (str[i])
	{
		write(1, &(str[i]), 1);
		i++;
	}
}

int	nflags(char **execute, int j, int i)
{
	if (execute[j][i - 1] == '-')
		return (0);
	i++;
	while (execute[j][i] == 'n')
		i++;
	if (execute[j][i] == 0)
		return (1);
	return (0);
}
/*
This code is part of a function that checks for the "-n" flag in a command line argument. 
The function takes in an array of strings (char **execute) and 
checks each element of the array to see if it contains the "-n" flag. 
If it does, it sets is_nflag to 1, otherwise it sets is_nflag to -1. 
If is_nflag is set to -1, the function returns 0. Otherwise, it returns 1.
*/
int	ft_echo_flag_check(char **execute)
{
	int		i;
	int		is_nflag;
	int		j;

	i = 0;
	j = 1;
	is_nflag = 0;
	while (execute[j])
	{
		if (execute[j][i] == '-' && is_nflag != -1 && \
			execute[j][i + 1] == 'n' && nflags(execute, j, i))
			is_nflag = 1;
		else
		{
			if (is_nflag == 0)
				is_nflag = -1;
			put_str(execute[j], 0);
			if (execute[j + 1] != 0)
				write(1, " ", 1);
		}
		j++;
	}
	if (is_nflag == -1)
		return (0);
	return (1);
}
/*
This code is part of a function that implements the built-in command "echo" in a shell. 
The function takes an array of strings (execute) as an argument. 
It first checks if there is anything after the "echo" command, and if not, 
it prints a new line character. It then checks for any flags (e.g. -n) and 
writes a new line character if no flags are present. 
Finally, it exits with the status code EXIT_SUCCESS if it is not the parent process.
*/

void	builtin_echo(char **execute)
{
	int		i;

	if (!execute[1])
	{
		write(1, "\n", 1);
	}
	i = ft_echo_flag_check(execute);
	if (!i)
		write(1, "\n", 1);
	if (!is_parent())
		exit(EXIT_SUCCESS);
}
