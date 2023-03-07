#include "../minishell.h"
/*This code creates a new array of strings, 
which is one element longer than the original array. 
The new element is the string 'str'. 
The original array is freed and the new one is returned.
*/
char	**push_array(char **arg_arr, char *str)
{
	int		i;
	int		len;
	char	**new_arr;

	i = 0;
	len = 0;
	while (arg_arr && arg_arr[len])
		len++;
	new_arr = ft_calloc(sizeof(char *), len + 2);
	while (i < len)
	{
		new_arr[i] = arg_arr[i];
		i++;
	}
	new_arr[i] = str;
	free(arg_arr);
	return (new_arr);
}
