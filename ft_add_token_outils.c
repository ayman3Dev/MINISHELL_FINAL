#include "minishell.h"

int ft_strlen_space(char *line)
{
	int size;
	int i;
	int count;

	if (line == NULL)
		return (0);
	count = 0;
	size = 0;
	i = -1;
	int sign = 0;
	while (line[++i] != '\0')
	{
		ft_check_quotes(line[i], &sign);
		if (sign == 0)
		{
			if (line[i] == '>' || line[i] == '<')
				count++;
			if ((line[i] != '>' && line[i] != '<') || count == 2)
				count  = 0;
			if (i > 0 && (line[i] == '|' || line[i - 1] == '|'))
				size++;
			if (i >= 1)
			{
				if (count == 1 && line[i - 1] != ' ' && (line[i] == '>' || line[i] == '<'))
					size++;
				else if ((line[i] == '>' || line[i] == '<') && line[i - 1] != ' ' && line[i - 1] != '>' && line[i - 1] != '<')
					size++;
			}
			if (line[i] == '>' || line[i] == '<')
			{
				if ((line[i] == '>' && line[i + 1] == '<') || (line[i] == '<' && line[i + 1] == '>'))
					size++;
				else if (line[i + 1] != ' ' && line[i + 1] != '>' && line[i + 1] != '<' && line[i + 1] != '\0')
					size++;
			}
		}
		size++;
	}
	return (size);
}

int check_pipe_char(char one)
{
	if ((one != ' ')
		&& (one != '"')
		&& (one != '\t')
		&& (one != '<')
		&& (one != '>'))
		return (1);
	return (0);
}
char *line_with_space(char *line)
{
	int i = 0;
	int j = 0;
	int count = 0;
	int sign = 0;
	if (line == NULL)
		return(NULL);
	int size_space = ft_strlen_space(line);
	if (size_space == 0)
		return (line);
	char *line_copy = malloc(size_space + 1);
	if (line_copy == NULL)
		return (NULL);
	while (line[i] != '\0')
	{
		ft_check_quotes(line[i], &sign);
		if (sign == 0)
		{
			if (line[i] == '>' || line[i] == '<')
				count++;
			if ((line[i] != '>' && line[i] != '<') || count == 2)
				count  = 0;
			if (i > 0 && (line[i] == '|') && ((check_pipe_char(line[i + 1]) == 1)))
				line_copy[j++] = ' ';
			if ((line[i + 1] == '|') && ((check_pipe_char(line[i]) == 1)))
			{
				puts("ok");
				line_copy[j++] = line[i];
				line_copy[j++] = ' ';
			}
			if (i >= 1)
			{
				if (count == 1 && line[i - 1] != ' ' && (line[i] == '>' || line[i] == '<'))
					line_copy[j++] = ' ';
				else if ((line[i] == '>' || line[i] == '<') && line[i - 1] != ' ' && line[i - 1] != '>' && line[i - 1] != '<')
					line_copy[j++] = ' ';
			}
			if (line[i] == '>' || line[i] == '<')
			{
				if ((line[i] == '>' && line[i + 1] == '<') || (line[i] == '<' && line[i + 1] == '>'))
				{
					line_copy[j++] = line[i++];
					line_copy[j++] = ' ';
				}
				else if (line[i + 1] != ' ' && line[i + 1] != '>' && line[i + 1] != '<' && line[i + 1] != '\0')
				{
					line_copy[j++] = line[i++];
					line_copy[j++] = ' ';
				}
			}
		}
		line_copy[j++] = line[i];
		i++;
	}
	line_copy[j] = '\0';
	printf("%s\n", line_copy);
	return(line_copy);
}

