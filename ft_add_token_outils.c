#include "minishell.h"

int ft_strlen_space(char *line)
{
	if (line == NULL)
		return (0);
	int size;
	int i;

	size = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			if (i > 0 && (line[i - 1] != ' ' && line[i - 1] != '\t' && line[i - 1] != '>' && line[i - 1] != '<' &&  line[i - 1] != '|' ))
			{
				size++;
			}
			if (line[i + 1] == line[i])
			{
				i++;
				i++;
				if (line[i] != ' ')
					size++;
			}
			else
				{
					i++;
					size++;
				}
		}
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
			continue;
		if (line[i] == '\0')
			break;
		i++;
	}
	printf("size : %d\n", size);
	return (size);
}

char *line_with_space(char *line)
{
	int i = 0;
	int j = 0;
	if (line == NULL)
		return(NULL);
	int size_space = ft_strlen_space(line);
	if (size_space == 0)
		return (line); // or ft_strdup(line);
	char *line_copy = malloc(size_space + strlen(line) + 1);
	if (line_copy == NULL)
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			if (i > 0 && (line[i - 1] != ' ' && line[i - 1] != '\t' && line[i - 1] != '>' && line[i - 1] != '<' &&  line[i - 1] != '|' ))
			{
				line_copy[j++] = ' ';
			}
			if (line[i + 1] == line[i])
			{
				line_copy[j++] = line[i++];
				line_copy[j++] = line[i++];
				if (line[i] != ' ')
					line_copy[j++] = ' ';
			}
			else
			{
				line_copy[j++] = ' ';
				line_copy[j++] = line[i++];
			}
		}
		if (line[i] == '<' || line[i] == '>')
			continue;
		if (line[i] == '\0')
			break;
		line_copy[j++] = line[i];
		i++;
	}
	line_copy[j] = '\0';
	printf("line_copy : %s\n", line_copy);
	return(line_copy);
}
