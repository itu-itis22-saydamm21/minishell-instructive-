#include "../minishell.h"

int	env_len(void)
{
	char	**env;

	env = g_ms.env;
	while (*env)
		env++;
	return (env - g_ms.env);
}

int	check_env(char *str)
{
	char	*head;

	head = ft_strchr(str, '=');
	if (!head)
		return (FALSE);
	if (head == str)
		return (FALSE);
	while (*str)
	{
		if (is_whitespace(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
/*
This code adds an environment variable to the global environment array. 
It begins by creating a new array of size env_len() + 2 and 
copying all the elements from the existing global environment array into it. 
It then adds a new element to the end of this array, which is passed in as a parameter (str). 
Finally, it frees the existing global environment array and assigns the new one to it.

*/
void	add_env(char *str)
{
	int		i;
	char	**env;
	char	**new_env;

	i = 0;
	env = g_ms.env;
	new_env = ft_calloc(sizeof(char **), env_len() + 2);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	free_array(g_ms.env);
	g_ms.env = new_env;
}

/*This code is checking if a given string (str) is included in the environment variables. 
It does this by looping through the environment variables (env) and 
comparing each character of the given string to each character of the environment variable. 
If all characters match, it returns the index of the environment variable. 
If there is no match, it returns -1.*/

int	is_include(char *str)
{
	int		i;
	int		j;
	char	**env;

	i = 0;
	env = g_ms.env;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && str[j])
		{
			if (str[j] == '=' && env[i][j] == '=')
				return (i);
			if (str[j] != env[i][j])
				break ;
			j++;
		}
		i++;
	}
	return (-1);
}
/*
This code takes in an array of strings (input) and 
sets the environment variables for the shell. 
It first checks if the environment variable exists, and 
if it does, it updates it with the new value. If it doesn't exist, 
it adds the environment variable to the list of variables. 
Finally, it sets the paths for the shell and exits if it is not a parent process.

*/
void	builtin_export(char **input)
{
	int		pos;
	char	*tmp;

	input++;
	while (*input)
	{
		if (check_env(*input))
		{
			pos = is_include(*input);
			if (pos != -1)
			{
				tmp = g_ms.env[pos];
				g_ms.env[pos] = ft_strdup(*input);
				free(tmp);
			}
			else
				add_env(*input);
		}
		input++;
	}
	set_paths();
	if (!is_parent())
		exit (EXIT_SUCCESS);
}
