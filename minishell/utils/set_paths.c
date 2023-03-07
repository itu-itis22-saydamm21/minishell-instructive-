#include "../minishell.h"
/*This code is setting the paths for a program. 
It is first checking if the paths have already been set, and if so, it frees them. 
It then gets the environment variable "PATH" and checks if it is empty. 
If it is empty, it sets the paths to NULL. 
Otherwise, it splits the path by ':' and sets the paths to that value. 
Finally, it frees the path variable.*/
void	set_paths(void)
{
	char	*path;

	if (g_ms.paths)
		free_array(g_ms.paths);
	path = get_env("PATH");
	if (!(*path))
		g_ms.paths = NULL;
	else
		g_ms.paths = ft_split(path, ':');
	free(path);
}
