#include "../minishell.h"
/*
This code is a function that checks if a given character string is an operator. 
It checks for the operators '<<', '>>', '<', '>', and '|'. 
If any of these operators are found, it returns an integer value corresponding to 
the operator. Otherwise, it returns 0.

*/
int	is_operator(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '<' && str[1] == '<')
		return (HERE_DOC);
	if (str[0] == '>' && str[1] == '>')
		return (RED_APPEND);
	if (str[0] == '<')
		return (RED_INPUT);
	if (str[0] == '>')
		return (RED_OUTPUT);
	if (str[0] == '|')
		return (PIPE);
	return (0);
}
