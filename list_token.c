#include "minishell.h"

t_word *ft_list_tokn(char *all_command, t_word *token)
{
	if (all_command == NULL)
		return (NULL);
	char *line = line_with_space(all_command);
	if (line == NULL)
		return (NULL);
	int i = 0;
	int j = 0;
	int size = 0;

	char *value = NULL;
	t_word *word = NULL;
	while (line[i] != '\0')
	{

		j = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0')
			break;
		size = 0;
		while (line[i + size] != ' ' && line[i  + size] != '\t' && line[i + size] != '\0')
			size++;
		value = malloc(size + 1);
		if (value == NULL)
			return (NULL);
		while (j < size)
		{
			value[j] = line[i];
			i++;
			j++; 
		}
		value[j] = '\0';
		word = ft_addlist_token(value);
		if (word == NULL)
		{
			free(value);
			free(line);
			return(NULL);	
		}
		ft_lstaddback_token(&token, word);
		free(value);
		if (line[i] != '\0')
			i++;
	}
	return(token);
}

int check_syntax(t_word *token)
{
	if (token == NULL)
		return(1);
	if (token->type == PIPE)
	{
		return(write(1, "syntax error near unexpected token `|'\n", 39), 1);
	}
	while(token != NULL)
	{
		if (token->type == PIPE && token->next == NULL)
			return(write(1, "syntax error near unexpected token `|'\n", 39), 1);
		if (token->next)
		{
			if ((token->next->type == L_RED || token->next->type == R_RED || token->next->type == DR_RED || token->next->type == DL_RED || token->next->type == PIPE))
			{
				if (token->type == L_RED)
					return(write(1, "syntax error near unexpected token `<'\n ", 40), 2);
				else if (token->type == R_RED)
					return(write(1, "syntax error near unexpected token `>'\n ", 40), 2);
				else if (token->type == DL_RED)
					return(write(1, "syntax error near unexpected token `<<'\n ", 41), 2);
				else if (token->type == DR_RED)
					return(write(1, "syntax error near unexpected token `>>'\n ", 41), 2);
				else if (token->type == PIPE)
					return(write(1, "syntax error near unexpected token `|'\n ", 41), 2);
			}
		}
		token = token->next;
	}
	return (0);
}
int	ft_check_line(char *line)
{
	int	i;
	int	sign;

	sign = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|' && line[i + 1] == '|' && sign == 0)
			return (write(2, "syntax error near unexpected token `|'\n", 39), 1);
		ft_check_quotes(line[i], &sign);
		i++;
	}
	if (sign != 0)
		return (write(1, "syntax error\n", 13), 2);
	return (0);
}

// int	ft_check_line(char *line)
// {
// 	int	i;
// 	int	sign;
// 	int	size;

// 	size = 0;
// 	sign = 0;
// 	i = 0;
// 	while (line[i] != '\0')
// 	{
// 		ft_check_quotes(line[i], &sign);
// 		i++;
// 	}
// 	if (sign != 0)
// 		return (write(1, "syntax error\n", 13), 1);
// 	sign = 0;
// 	i = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == ' ')
// 		{
// 			while (line[i] == ' ' || line[i] == '\t')
// 				i++;
// 		}
// 		ft_check_quotes(line[i], &sign);
// 		if (line[i])
// 			size++;
// 		if (line[i] == '|' && size == 1)
// 			return (write(1, "syntax error near unexpected token `|'\n", 39), 1);
// 		if (line[i] == '|')
// 		{
// 			i++;
// 			while(line[i] == ' ' || line[i] == '\t')
// 				i++;
// 			if(size == 1 || (line[i] == '|' && sign == 0) || line[i] == '\0')
// 				return(write(1, "syntax error near unexpected token `|'\n", 39), 1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }