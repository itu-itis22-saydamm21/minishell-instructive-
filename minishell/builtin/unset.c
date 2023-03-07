#include "../minishell.h"
/*
This code removes an environment variable from the global environment array g_ms.env. 
It takes in a char *data as an argument, 
which is the name of the environment variable to be removed. 
It creates a new array called new_env and iterates through g_ms.env, 
copying all elements except for the one that matches data into new_env. 
At the end, it frees g_ms.env and sets it equal to new_env.

*/
void	remove_env(char *data)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_calloc(sizeof(char *), env_len() + 1);
	while (g_ms.env[i])
	{
		if (ft_strncmp(g_ms.env[i], data, ft_strlen(data)))
		{
			new_env[j] = ft_strdup(g_ms.env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = 0;
	free_array(g_ms.env);
	g_ms.env = new_env;
}
/*This code is part of a shell program. 
It is a function that handles the built-in command "unset". 
The function takes in an array of strings, 
which are the arguments passed to the unset command. 
It then iterates through each argument and creates a string 
by joining it with an equal sign. 
This string is then passed to another function, remove_env(), 
which removes the environment variable associated with that string from the environment. 
After all arguments have been processed, it sets the paths and 
exits if it is not the parent process.*/
void	builtin_unset(char **input)
{
	char	*data;

	input++;
	while (*input)
	{
		data = ft_strjoin(*input, "=");
		remove_env(data);
		free(data);
		input++;
	}
	set_paths();
	if (!is_parent())
		exit (EXIT_SUCCESS);
}
