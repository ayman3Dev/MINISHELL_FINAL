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
		while (ft_is_space(all_command[i]) == 1)  // all_command[i] != '\0'
			i++;
		if (all_command[i] == '\0')
			break;
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
				ft_check_quotes(all_command[i], &sign);
			}
			word = ft_addlist_token(ft_substr(all_command, size, i - size));
		}
		ft_lstaddback_token(&token, word);
	}
	// t_word *tmp = token;
	// while(tmp != NULL)
	// {
	// 	printf("word : {%s}    type: %d\n", tmp->value, tmp->type);
	// 	tmp = tmp->next;
	// }
	return(token);		
}

int lenght_no_quotes(t_word *token)
{
	int	i;
	int	sign;
	int	quotes;

	i = 0;
	sign = 0;
	quotes = 0;
	while (token->value[i] != '\0')
	{
		ft_check_quotes(token->value[i], &sign);
		if (sign != 0)
		{
			while (sign != 0)
			{
				i++;
				ft_check_quotes(token->value[i], &sign);
			}
			quotes += 2;
		}
		i++;
	}
	return (i - quotes);
}


/*if (sign != 0)
			{
				while (sign != 0)
				{
					i++;
					ft_check_quotes(token->value[i], sign);
					if (sign != 0)
					{
						token->val_noquotes[j] = token->value[i];
						j++;
					}
				}
				i++;
				quotes += 2;
			}*/
int remove_quotes(t_word *token)
{
	t_word *tmp = token;
	int	quotes;
	int	sign;
	int	i;
	int	j;

	while (token)
	{
		i = 0;
		j = 0;
		sign = 0;
		quotes = 0;
		token->val_noquotes = malloc(lenght_no_quotes(token) + 1);
		while (token->value[i] != '\0')
		{
			ft_check_quotes(token->value[i], &sign);
			if (sign != 0)
			{
				i++;
				ft_check_quotes(token->value[i], &sign);
				while (sign != 0)
				{
					token->val_noquotes[j] = token->value[i];
					j++;
					i++;
					ft_check_quotes(token->value[i], &sign);
				}
				i++;
				quotes += 2;
			}
			else
			{
				token->val_noquotes[j] = token->value[i];
				i++;
				j++;

			}
		}
		token->val_noquotes[j] = '\0';
		token = token->next;
	}
	while(tmp != NULL)
	{
		printf("word : {%s}\n", tmp->val_noquotes);
		tmp = tmp->next;
	}
	return (0);
}