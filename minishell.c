#include "minishell.h"

void ft_minishell(char *line)
{
	t_word	*token;

	token = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		add_history(line);
		ft_check_line(line);
		token  = ft_list_tokn(line, token);
		if (check_syntax(token) == 1)
		{
			ft_lstclear_token(&token);
			continue;
		}
		ft_lstclear_token(&token);
		free(line);
	}
}
int main (int argc, char **argv, char **env)
{
	char	*line;

	(void)env;
	(void)argc;
	(void)argv;

	line = NULL;
	ft_minishell(line);
}