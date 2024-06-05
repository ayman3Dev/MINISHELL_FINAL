#include "minishell.h"


int check_syntax(t_word *token)
{
	// puts("ok");
	if (token == NULL)
		return(1);
	if (token->type == PIPE)
		return(write(1, "syntax error near unexpected token `|'\n", 39), 1);
	while(token != NULL)
	{
		if ((token->type == PIPE && token->next == NULL) || (token->type == PIPE && token->next->type == PIPE))
			return(write(1, "syntax error near unexpected token `|'\n", 39), 1);
		if (token->next)
		{
			if ((token->next->type == L_RED || token->next->type == R_RED || token->next->type == DR_RED || token->next->type == DL_RED || token->next->type == PIPE))
			{
				if (token->type == L_RED)
					return(write(1, "syntax error near unexpected token `<'\n", 39), 1);
				else if (token->type == R_RED)
					return(write(1, "syntax error near unexpected token `>'\n", 39), 1);
				else if (token->type == DL_RED)
					return(write(1, "syntax error near unexpected token `<<'\n", 40), 1);
				else if (token->type == DR_RED)
					return(write(1, "syntax error near unexpected token `>>'\n", 40), 1);
				else if (token->type == PIPE)
					return(write(1, "syntax error near unexpected token `|'\n", 40), 1);
			}
		}
		token = token->next;
	}
	return (0);
}