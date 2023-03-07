#include "minishell.h"

void	init_shell(char *input)
{
	g_ms.token = NULL;
	_ms.process = NULL;
	g_ms.process_count = 0;
	tokenize(input);
	if (!lexer())
		return ;
	start_cmd();
	free_process();
}
/*

This code is a signal handler for the SIGINT signal (Ctrl-C). 
When the user presses Ctrl-C, the signal handler sets g_ms.exit_code to 1, 
sets g_ms.ignore to TRUE, 
and sends a newline character to the terminal using ioctl(). 
It then writes "\033[A" (an ANSI escape sequence(^)) to the terminal 
which moves the cursor up one line. 

*/
void	ctrl_c(int sig)
{
	(void)sig;
	g_ms.exit_code = 1;
	g_ms.ignore = TRUE;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}
/*
This code checks if the input is NULL. If it is, 
it prints "exit" and exits the program with the exit code stored 
in g_ms.exit_code.
*/
void	ctrl_d(char *input)
{	
	if (!input)
	{
		printf("\nexit\n");
		exit(g_ms.exit_code);
	}
}
/*
This code sets up a signal handler for the SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) signals. 
The signal handler, ctrl_bs, sets g_ms.ignore to TRUE and 
then sets up a new signal handler for SIGINT called ctrl_c. 
It also sets up a signal handler for SIGQUIT that ignores the signal.*/
void	ctrl_bs(int sig)
{
	(void)sig;
	g_ms.ignore = TRUE;
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
