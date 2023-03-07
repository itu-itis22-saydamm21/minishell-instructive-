#include "../minishell.h"
/*This code is a function that takes in two parameters, a pointer to a character pointer 
(char **new_str) and a character pointer (char *str). 
It first checks if the character pointer new_str is empty. 
If it is, it assigns the string pointed to by str to new_str 
using ft_strdup and then frees str. If new_str is not empty, 
it creates a temporary variable tmp that points to the same string as new_str.
It then assigns the result of ft_strjoin(*new_str, str) to new_str and 
frees both tmp and str. This function essentially combines two strings into one and 
assigns the combined string to new_str.
*/
void	push_new_str(char **new_str, char *str)
{
	char	*tmp;

	if (!(*new_str))
	{
		*new_str = ft_strdup(str);
		free(str);
		return ;
	}
	tmp = *new_str;
	*new_str = ft_strjoin(*new_str, str);
	free(tmp);
	free(str);
}
/*This code takes a string (str), a position (pos) and a type (type) as parameters. 
It then increments the position by 1. It sets the first variable to the new position. 
It then loops through the string, incrementing the position until it finds a character 
that matches the type parameter or until it reaches the end of the string. 
It then creates a new string with ft_substr, using the first variable 
as its starting point and pos - first as its length. 
Finally, if str[*pos] is true, it increments pos by 1 and returns new_str.*/
char	*clean_quote_with_type(char *str, int *pos, char type)
{
	int		first;
	char	*new_str;

	(*pos)++;
	first = *pos;
	while (str[*pos] && str[*pos] != type)
		(*pos)++;
	new_str = ft_substr(str, first, *pos - first);
	if (str[*pos])
		(*pos)++;
	return (new_str);
}
/*his code takes in two parameters, a string (str) and a position (pos). 
It then sets the variable "first" to the value of the position. 
It then enters a while loop that will continue 
until it encounters either a double quote or a single quote character in the string, 
or until it reaches the end of the string. As it goes through each character in the string, it increments the position by 1. Once it has reached either a double quote or single quote character, or reached the end of the string, it returns a substring of str from "first" to "pos - first".*/

static char	*get_str(char *str, int	*pos)
{
	int	first;

	first = *pos;
	while (str[*pos] && str[*pos] != DOUBLE_QUOTE && str[*pos] != SINGLE_QUOTE)
		(*pos)++;
	return (ft_substr(str, first, *pos - first));
}

/*This code is used to clean up a string by removing quotes. 
It takes in a string as an argument, 
then checks each character of the string for either double or single quotes. 
If it finds either type of quote, it will call the clean_quote_with_type() function 
to remove the quote and any characters between them. 
If it finds any other character, it will call the get_str() function 
to add that character to a new string. 
Finally, it will return the new string with all quotes removed.
*/
char	*clean_quote(char *str)
{
	int		i;
	char	*data;
	char	*result;

	i = 0;
	result = NULL;
	str = dollar(str);
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOTE)
			data = clean_quote_with_type(str, &i, DOUBLE_QUOTE);
		else if (str[i] == SINGLE_QUOTE)
			data = clean_quote_with_type(str, &i, SINGLE_QUOTE);
		else
			data = get_str(str, &i);
		push_new_str(&result, data);
	}
	free(str);
	return (result);
}
