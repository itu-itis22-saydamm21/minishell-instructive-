#include "../minishell.h"

int	ft_get_arg_count(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	return (i);
}

int	ft_isnumber_with_sign(char *arg)
{
	while (*arg)
	{
		if ((*arg >= '0' && *arg <= '9') || *arg == '+' || *arg == '-')
			arg++;
		else
			return (FALSE);
	}
	return (TRUE);
}
/*                        
This code is a function that exits the program. 
It checks if there is one argument, and if so, 
it prints "exit" and exits the program with the exit code stored in g_ms.exit_code. 
If there are more than one argument, it checks if the second argument is a number 
with a sign, and if so, it exits the program with the exit code being the number modulo 256.
If not, it prints an error message and exits with an exit code of -1 modulo 256.*/
void	builtin_exit(char **input)
{
	if (ft_get_arg_count(input) == 1)
	{
		printf("exit\n");
		exit(g_ms.exit_code);
	}
	else
	{
		if (ft_isnumber_with_sign(input[1]))
		{
			if (ft_get_arg_count(input) > 2)
			{
				write(2, "exit\nminishell: exit: too many arguments\n", 41);
				g_ms.exit_code = 1;
				return ;
			}
			exit(ft_atoi(input[1]) % 256);
		}
		write(2, "exit\nminishell: exit: numeric argument required\n", 48);
		exit(-1 % 256);
	}
}
