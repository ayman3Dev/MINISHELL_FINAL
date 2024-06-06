#include "minishell.h"

void f()
{
	system("leaks minishell");
}
void	ft_minishell(char *line)
{
	t_word	*token;
	t_red_node	*files;
	
	files = NULL;
	token = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		if (check_quotes(line) == 1)
		{
			return ;
			free(line); 
			 continue ;
		}
		token = ft_list_tokn(line, token);
		if (token == NULL || check_syntax(token) == 1)
		{
			ft_lstclear_token(&token);
			free(line);
			return ;
			continue ;
		}
		remove_quotes(token);
		ft_list_file(token, files);
		ft_lstclear_token(&token);
		
		free(line);
		return ;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	atexit(f);
	(void)env;
	(void)argc;
	(void)argv;
	line = NULL;
	ft_minishell(line);
}