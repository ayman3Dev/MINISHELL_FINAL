#include "minishell.h"

void ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
}

t_word *ft_list_tokn(char *all_command, t_word *token)
{
	char *line;
	int i = 0;
	char **all_split;

	if (all_command == NULL)
		return (NULL);
	line = line_with_space(all_command);
	if (line == NULL)
		return (NULL);
	all_split = ft_split(line, ' ');
	if (all_split == NULL)
		return (NULL);
	free(line);
	t_word *word = NULL;
	while (all_split[i])
	{
		word = ft_addlist_token(all_split[i]);
		if (word == NULL)
			return(NULL);
		ft_lstaddback_token(&token, word);
		i++;
	}
	if (token == NULL)
		ft_free_split(all_split);
	return(token);
}