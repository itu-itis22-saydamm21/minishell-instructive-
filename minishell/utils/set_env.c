#include "../minishell.h"
/*This code sets the environment variables. 
It takes in a char** (an array of strings) as an argument and 
stores it in a global variable called g_ms.env. 
It first finds the length of the array and allocates enough memory to 
store the strings in the array. Then, it iterates through each element of the array, 
duplicating each string and storing it in g_ms.env. 
Finally, it sets the last element of g_ms.env to NULL.*/
void	set_env(char **env)
{
	size_t	i;
	size_t	len;
	char	**head;

	head = env;
	while (*head)
		head++;
	len = head - env;
	g_ms.env = ft_calloc(sizeof(char **), len + 1);
	i = -1;
	while (++i < len)
		g_ms.env[i] = ft_strdup(env[i]);
}
