#include "minishell.h"

t_word *ft_list_tokn(char *all_command, t_word *token)
{
	int	i;
	int	sign;
	int	size;
	t_word *word;

	word = NULL;
	size= 0;
	sign = 0;
	i = 0;
	while(all_command[i] != '\0')
	{
		while (ft_is_space(all_command[i]) == 1) // all_command[i] != '\0'
			i++;
		ft_check_quotes(all_command[i], &sign);
		if (sign == 0 && ((all_command[i] == '>' && all_command[i + 1] == '>')
				|| (all_command[i] == '<' && all_command[i + 1] == '<')))
		{
			word = ft_addlist_token(ft_substr(all_command, i, 2));
			i += 2;
		}
		else if (sign == 0 && ((check_char(all_command[i])) != NULL))
		{
			word = ft_addlist_token(ft_strdup((check_char(all_command[i]))));
			i++;
		}
		else
		{
			size = i;
			while ((check_space(all_command[i], sign)) == 1 && all_command[i] != '\0')
			{
				i++;
				// printf("before sign : %d      ", sign);
				ft_check_quotes(all_command[i], &sign);
				// printf("sign : %d\n", sign);
			}
			word = ft_addlist_token(ft_substr(all_command, size, i - size));
		}
		ft_lstaddback_token(&token, word);
	}
	puts("token\n");
	while(token != NULL)
	{
		printf("word : {%s}    type: %d\n", token->value, token->type);
		token = token->next;
	}
	return(token);
}
