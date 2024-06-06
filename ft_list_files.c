#include "minishell.h"

void ft_list_file(t_word	*token, t_red_node *files)
{
	while (token != NULL)
	{
		if (check_red(token->type) == 1)
		{
			files->red = 
		}
		token = token->next;
	}
}
