#include "minishell.h"

int ft_check_quotes(char c, int *sign)
{
	if (c == '"' && *sign == 1)
		*sign = 0;
	else if (c == '\'' && *sign == 2)
		*sign = 0;
	else if (c == '"')
		*sign = 1;
	else if (c == '\'')
		*sign = 2;
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