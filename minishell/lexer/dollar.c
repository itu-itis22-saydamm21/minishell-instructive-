#include "../minishell.h"

int	valid_op(char c)
{
	return ((c >= 'a' && c <= 'z') || \
			(c >= 'A' && c <= 'Z') || \
			(c >= '0' && c <= '9') || \
			(c == '_') || (c == '?'));
}
/*This code checks if a dollar sign is present in a string and if it is, 
it checks if the character after the dollar sign is valid. 
It does this by looping through the string until it finds a dollar sign, 
then checking if the character after it is valid. 
It also keeps track of single and double quotes to make sure that they are not 
inside of a quoted string when the dollar sign is found. 
If everything is valid, it returns TRUE, otherwise FALSE.*/
int	check_dollar(char *str)
{
	int		i;
	int		single_quote;
	int		double_quote;

	i = 0;
	single_quote = TRUE;
	double_quote = FALSE;
	while (str[i] && str[i] != DOLLAR_OP)
	{
		if (str[i] == SINGLE_QUOTE)
			single_quote = double_quote;
		if (str[i] == DOUBLE_QUOTE)
			double_quote = !double_quote;
		i++;
	}
	if (!valid_op(*(ft_strchr(str, DOLLAR_OP) + 1)))
		return (FALSE);
	return (single_quote);
}

static char	*get_str(char *str, int	*pos, int type)
{
	int		first;
	char	*data;

	first = *pos;
	while (str[*pos] != type)
		(*pos)++;
	data = ft_substr(str, first, *pos - first);
	(*pos)++;
	return (data);
}
/*This code is used to parse a string for a dollar operator. 
It takes in a string as an argument and returns a pointer to the result. 
The code first initializes several variables, such as i, first, env, result, and data. 
It then sets the result to NULL and gets the string from the argument str with get_str(). 
It then pushes the new string onto the result. 
The code then checks if the character at str[i] is '?' and 
if so it pushes the exit code of g_ms onto the result. 
If not, it will loop through while valid_op(str[i]) is true and increment i each time. 
It then gets a substring from str starting at first and ending at i - first and 
assigns it to data. It then gets an environment variable with get_env() using data 
as an argument and pushes that onto the result. 
Finally, it gets another string from str with get_str() and 
pushes that onto the result before returning it.
*/
char	*parse_dollar_op(char *str)
{
	int		i;
	int		first;
	char	*env;
	char	*result;
	char	*data;

	i = 0;
	result = NULL;
	data = get_str(str, &i, DOLLAR_OP);
	push_new_str(&result, data);
	first = i;
	if (str[i] == '?' && ++i)
		push_new_str(&result, ft_itoa(g_ms.exit_code));
	else
	{
		while (valid_op(str[i]))
			(i)++;
		data = ft_substr(str, first, i - first);
		env = get_env(data);
		push_new_str(&result, env);
		free(data);
	}
	data = get_str(str, &i, 0);
	push_new_str(&result, data);
	return (result);
}
/*
This code takes in a string (str) and creates a duplicate of it (new_str). 
It then checks if the new_str contains the character '$' and checks if it is valid. 
If both conditions are true, it calls parse_dollar_op() on new_str, 
which returns a modified version of new_str. 
The original version of new_str is then freed and the modified version is returned.
*/

char	*dollar(char *str)
{
	char	*tmp;
	char	*new_str;

	new_str = ft_strdup(str);
	while (ft_strchr(new_str, DOLLAR_OP) && check_dollar(new_str))
	{
		tmp = new_str;
		new_str = parse_dollar_op(new_str);
		free(tmp);
	}
	return (new_str);
}
