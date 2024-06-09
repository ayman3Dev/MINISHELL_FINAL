#include "minishell.h"

void f()
{
	system("leaks minishell");
}
void	ft_minishell(char *line, char **env)
{
	t_word		*token;
	t_red_node	*files;
	t_cmd_node	*cmd;
	t_env		*envirment;

	envirment = NULL;
	cmd = NULL;
	files = NULL;
	token = NULL;
	ft_env(env, &envirment);
	while (1)
	{
		line = readline("mash$ ");
		if (!line)
			break ;
		add_history(line);
		if (check_quotes(line) == 1)
			continue ;
		token = ft_list_tokn(line, token, envirment);
		remove_quotes(token);
		if (token == NULL || check_syntax(token) == 1)
		{
			ft_lstclear_token(&token);
			free(line);
			continue ;
		}
		ft_list_file(token, files);
		ft_list_cmd (token, cmd);
		ft_lstclear_token(&token);
		free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	// atexit(f);
	(void)argc;
	(void)argv;
	line = NULL;
	ft_minishell(line, env);
}