#include "../minishell.h"
/*This code is a function that prints the current working directory. 
It begins by using the getcwd() function to get the current working directory and 
store it in a variable called "result". If "result" is NULL, 
then an error message is printed. Otherwise, the current working directory is printed. 
The memory allocated for "result" is then freed, and 
if the process is not a parent process, 
then it exits with the exit code stored in g_ms.exit_code.
*/
void	builtin_pwd(void)
{
	char	*result;

	result = getcwd((void *)0, 0);	//This code calls the getcwd() function, 
									//which is used to get the current working directory of
									// the process. The first argument is a pointer to 
									//a buffer that will be filled with the path of the 
									//current working directory. In this case,
									//it is set to NULL (void *)0, so no buffer will be used 
									//and the path will be returned as a string. 
									//The second argument is the size of the buffer in bytes, 
									//which is set to 0 in this case.
	if (!result)
		perror("minishell ");
	else
		printf("%s\n", result);
	free(result);
	if (!is_parent())
		exit(g_ms.exit_code);
}
