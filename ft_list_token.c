#include "minishell.h"

// t_word	*ft_list_tokn(char *all_command, t_word *token, t_env *envirment)
// {
// 	int		i;
// 	int		sign;
// 	int		size;
// 	t_word	*word;
// 	t_env *env_node;

// 	word = NULL;
// 	env_node = NULL;
// 	size = 0;
// 	sign = 0;
// 	i = 0;
// 	while (all_command[i] != '\0')
// 	{
// 		while (ft_is_space(all_command[i]) == 1)  // all_command[i] != '\0'
// 			i++;
// 		if (all_command[i] == '\0')
// 			break ;
// 		ft_check_quotes(all_command[i], &sign);
// 		word = ft_addlist_token(ft_substr(all_command, size, i - size));
// 		ft_lstaddback_token(&token, word);
// 	}
// 	// t_word *tmp = token;
// 	// while(tmp != NULL)
// 	// {
// 	// 	printf("word : {%s}    type: %d\n", tmp->value, tmp->type);
// 	// 	tmp = tmp->next;
// 	// }
// 	return (token);		
// }

t_word	*ft_list_tokn(char *all_command, t_word *token, t_env *envirment)
{
	int		i;
	int		sign;
	int		size;
	t_word	*word;
	t_env *env_node;

	word = NULL;
	env_node = NULL;
	size = 0;
	sign = 0;
	int check = 0;
	int c = 0;
	i = 0;
	while (all_command[i] != '\0')
	{
		size = 0;
		check = 0;
		c = 0;
		while (ft_is_space(all_command[i]) == 1)  // all_command[i] != '\0'
			i++;
		if (all_command[i] == '\0')
			break ;
		//zyada
		while (all_command[i] == '$' || (all_command[i] == '"' && all_command[i + 1] == '$'))
		{
			size++;
			i++;
		}
		i = i - size;
		size = size % 2;
		ft_check_quotes(all_command[i], &sign);
		if ((size != 0 || (all_command[i] == '"' && all_command[i + 1] == '$')) && sign != 1)
		{
			if (sign == 2)
				i++;
			while (all_command[i] == '$')
				i++;
			char *name = get_variabl(all_command + i);
			env_node = point_node(envirment, name);
			if (env_node == NULL)
			{
				while (check_char_expand (all_command[i]) == 1)
					i++;
				continue;
			}
			word = ft_addlist_token(ft_strdup(env_node->value));
			while (check_char_expand (all_command[i]) == 1)
				i++;
			if (all_command[i] == '"')
			{
				sign = 0;
				i++;
			}
		}
		//zyada
		else if (sign == 0 && ((all_command[i] == '>' && all_command[i + 1] == '>')
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
			while ((check_space(all_command[i], sign)) == 1 && all_command[i])
			{
				i++;
				if (all_command[i] == '$' && c == 0 && sign != 1)
				{
					check = i;
					while (all_command[i] == '$')
					{
						c++;
						i++;
					}
					i = check;
					if (c % 2 != 0)
						break;
					else
						c = 1;
				}
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
	return (token);		
}

int	lenght_no_quotes(t_word *token)
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
	int	sign;
	int	i;
	int	j;

	while (token)
	{
		i = 0;
		j = 0;
		sign = 0;
		token->val_noquotes = malloc(lenght_no_quotes(token) + 1);
		token->quotes_type = 0;
		while (token->value[i] != '\0')
		{
			ft_check_quotes(token->value[i], &sign);
			if (sign != 0)
			{
				if (sign == 1)
					token->quotes_type = 1;
				else if (sign == 2)
					token->quotes_type = 2;
				i++;
				ft_check_quotes(token->value[i], &sign);// 7eyedha
				while (sign != 0)
				{
					token->val_noquotes[j] = token->value[i];
					j++;
					i++;
					ft_check_quotes(token->value[i], &sign);
				}
				i++;
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
	token = tmp;
	while(tmp != NULL)
	{
		printf("word : {%s} , type : %d\n", tmp->val_noquotes, tmp->quotes_type);
		tmp = tmp->next;
	}
	return (0);
}


//test
//echo  $hamza=1$23