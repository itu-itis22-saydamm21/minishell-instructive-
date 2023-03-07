#include "minishell.h"
/*
This code checks for a pipe character in a string and returns -1 if it finds one. 
It also removes any spaces from the beginning and end of the string, 
and (sets the string to 0).
*/
static int	pipe_space_check(int len, char *str)
{
	int	i;

	i = 0;
	while (str[i] == SPACE)
		i++;
	if (str[i] == '|')
		return (-1);
	while (str[len] == SPACE)
		len--;
	//str = 0;
	return (len);
}

/*
This code checks for the presence of a pipe character in a string. 
It first checks if the last character of the string is a pipe, and 
if it is, it prints an error message. It then loops through the string, 
looking for any pipe characters. If it finds two consecutive pipes, 
it sets all characters after the second one to 0. 
Finally, it returns TRUE if no errors were found.
*/
int	ft_pipecheck(char *str)
{
	int		len;
	int		i;
	char	c;

	i = 0;
	g_ms.process_count = 0;
	len = pipe_space_check(ft_strlen(str) - 1, str);
	if (len == -1 || str[len] == '|')
	{
		token_err(PIPE);
		return (FALSE);
	}
	while (str[i])
	{
		if (str[i] != SPACE && str[i] != TAB)
			c = str[i];
		i++;
		if (c == '|' && str[i] == '|')
		{
			while (len-- > i - 1)
				str[len] = 0;
		}
	}
	return (TRUE);
}
