#include "minishell.h"

char *check_char(char c)
{
	if (c == '|')
		return("|");
	if (c == '>')
		return (">");
	if (c == '<')
		return ("<");
	return (NULL);
}
int ft_is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
			return (1);
	return (0);
}
int check_space(char c, int sign)
{
	if (sign == 0)
	{
		if (c == 32 || (c >= 9 && c <= 13) || c == '|'
		|| c == '>' || c == '<' || c == '\0')
			return (0);

	}
	return(1);
}
