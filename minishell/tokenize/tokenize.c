#include "../minishell.h"
/*

This code creates a new token and initializes it with the given parameters. 
It allocates memory for the token using ft_calloc, which sets all fields of the token to 0.
The type field is set to the given type, and the str field is set to the given string. 
The prev and next fields are both set to NULL. 
Finally, it returns a pointer to the newly created token.

*/
t_token	*init_token(char *str, enum e_ttype type)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	token->type = type;
	token->str = str;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}
/*
This code is a function that checks if a given character string is an operator. 
It checks for the operators '<<', '>>', '<', '>', and '|'. 
If any of these operators are found, it returns an integer value corresponding
to the operator. Otherwise, it returns 0.
*/
int	token_addback(t_token **token, t_token *new_token, int plus)
{
	t_token	*i_token;

	i_token = *token;
	if (!i_token)
		*token = new_token;
	else
	{
		while (i_token->next)
			i_token = i_token->next;
		i_token->next = new_token;
		new_token->prev = i_token;
	}
	return (plus);
}
/*
This code is a function that takes in a character pointer (str) as an argument. 
It loops through each character in the string and 
checks if it is an operator using the is_operator() function. 
If it is an operator, it adds a token to g_ms.token with the corresponding operator and 
increments the string pointer by however many characters are in the operator. 
it is not an operator, it calls another function called parse_token_string() 
which parses the string for other tokens.
*/
void	tokenize(char *str)
{
	while (*str)
	{
		if (is_operator(str) == RED_APPEND)
			str += token_addback(&g_ms.token, init_token(ft_strdup(">>"), \
			RED_APPEND), 2);
		else if (is_operator(str) == HERE_DOC)
			str += token_addback(&g_ms.token, init_token(ft_strdup("<<"), \
			HERE_DOC), 2);
		else if (is_operator(str) == PIPE)
			str += token_addback(&g_ms.token, init_token(ft_strdup("|"), \
			PIPE), 1);
		else if (is_operator(str) == RED_INPUT)
			str += token_addback(&g_ms.token, init_token(ft_strdup("<"), \
			RED_INPUT), 1);
		else if (is_operator(str) == RED_OUTPUT)
			str += token_addback(&g_ms.token, init_token(ft_strdup(">"), \
			RED_OUTPUT), 1);
		else
			parse_token_string(&str);
	}
}
