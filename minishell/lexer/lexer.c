#include "../minishell.h"
/*
This code takes in two arguments, 
a pointer to a token and a pointer to a process. 
The token contains information about the command that the user has entered. 
The code checks if the type of the token is STRING,
which means it is an argument for the command. 
If it is, it pushes the argument into an array called execute and 
cleans any quotes from it. If it isn't, then it pushes the argument 
into an array called redirects and checks if there is another argument after it. 
If there isn't, then it prints out an error message and returns false. 
Otherwise, it cleans any quotes from the next argument and 
pushes that into redirects as well before returning true.
*/
int	append_arguments(t_token **token, t_process *process)
{
	char		*data;

	if ((*token)->type == STRING)
	{
		data = clean_quote((*token)->str);
		process->execute = push_array(process->execute, data);
	}
	else
	{
		data = clean_quote((*token)->str);
		process->redirects = push_array(process->redirects, data);
		*token = (*token)->next;
		if (!(*token) || (*token)->type != STRING)
		{
			free_token();
			if (!(*token))
				token_err(0);
			else
				token_err((*token)->type);
			return (FALSE);
		}
		data = clean_quote((*token)->str);
		process->redirects = push_array(process->redirects, data);
	}
	return (TRUE);
}
/*
This code is a lexer for a shell. It takes tokens from the token list, 
and creates processes out of them. It starts by checking if the token is a pipe or 
if it is the first token in the list. If it is, it creates a new process and 
adds it to the process list. It then appends arguments to that process 
until there are no more tokens left in the list. 
Finally, it frees up the token list and returns TRUE.
*/
int	lexer(void)
{
	t_token		*token;
	t_process	*process;

	token = g_ms.token;
	while (token)
	{
		if (token->type == PIPE || token->prev == NULL)
		{
			if (token->type == PIPE)
				token = token->next;
			process = init_process();
			process_addback(&g_ms.process, process);
			g_ms.process_count++;
		}
		if (!token)
			break ;
		if (!append_arguments(&token, process))
			return (FALSE);
		if (token)
			token = token->next;
	}
	free_token();
	return (TRUE);
}
