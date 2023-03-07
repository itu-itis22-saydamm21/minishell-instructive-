#include "../minishell.h"

void	find_end_pos(char **str, char type)
{
	(*str)++;
	while (**str)
	{
		if (**str == type)
		{
			(*str)++;
			if (is_whitespace(**str) || is_operator(*str))
				break ;
			else
				while (**str && !is_whitespace(**str) && !is_operator(*str))
					(*str)++;
			return ;
		}
		(*str)++;
	}
}

void	without_quote_parse(char **str)
{
	while (**str)
	{
		if (is_whitespace(**str))
			break ;
		if (is_operator(*str))
			break ;
		(*str)++;
	}
}

void	skip_whitespace(char **str, char **head)
{
	while (**str && is_whitespace(**str))
		(*str)++;
	*head = *str;
}
/*This code is used to parse a string of tokens. 
It starts by skipping any whitespace characters in the string, 
then checks if the first character is a double or single quote. 
If it is, it finds the end position of the quoted string. 
If not, it parses the string without quotes. 
It then gets the length of the token and creates a substring 
from the head position to that length. 
Finally, it adds this token to a list of tokens.*/
void	parse_token_string(char **str)
{
	int		len;
	char	*head;
	char	*token_str;

	skip_whitespace(str, &head);
	if (**str && **str == DOUBLE_QUOTE)
		find_end_pos(str, DOUBLE_QUOTE);
	else if (**str && **str == SINGLE_QUOTE)
		find_end_pos(str, SINGLE_QUOTE);
	else
		without_quote_parse(str);
	len = *str - head;
	if (len > 0)
	{
		token_str = ft_substr(head, 0, len);
		token_addback(&g_ms.token, init_token(token_str, STRING), 0);
	}
}
