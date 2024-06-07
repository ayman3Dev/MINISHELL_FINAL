#include "minishell.h"

int lenght_files (t_word	*token)
{
	int	size;
	t_word	*tmp;

	size = 0;
	tmp = token;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (check_red(tmp->type) == 1)
			size++;
		tmp = tmp->next;
	}
	return (size);
}

t_red_node	*ft_addlist_files(char **file, char **redirection)
{
	t_red_node	*new_node;

	if (file == NULL || redirection == NULL)
		return (NULL);
	new_node = (t_red_node *)malloc(sizeof(t_red_node));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->red = redirection;
	new_node->file = file;
	return (new_node);
}

t_cmd_node	*ft_addlist_cmds(char **commands)
{
	t_cmd_node	*new_node;

	if (commands == NULL)
		return (NULL);
	new_node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->command = commands;
	return (new_node);
}
void	ft_lstaddback_files(t_red_node **list, t_red_node *new_node)
{
	t_red_node	*tmp;

	tmp = *list;
	if (list == NULL || new_node == NULL)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	while ((*list)->next != NULL)
	{
		(*list) = (*list)->next;
	}
	(*list)->next = new_node;
	*list = tmp;
}

void	ft_lstaddback_cmd(t_cmd_node **list, t_cmd_node *new_node)
{
	t_cmd_node	*tmp;

	tmp = *list;
	if (list == NULL || new_node == NULL)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	while ((*list)->next != NULL)
	{
		(*list) = (*list)->next;
	}
	(*list)->next = new_node;
	*list = tmp;
}

void ft_list_file(t_word	*token, t_red_node *files)
{
	int	j;
	char **file;
	char **redirection;
	t_red_node *file_and_red;

	t_word	*tmp = token;
	files = NULL;
	while (token != NULL)
	{
		file = (char **)malloc(sizeof(char *) * lenght_files (token) + 1);
		if (file == NULL)
			return ;
		redirection = (char **)malloc(sizeof(char *) * lenght_files (token) + 1);
		if (redirection == NULL)
			return;
		if (token->type == PIPE)
			token = token->next;
		else
		{
			j = 0;
			while (token->type != PIPE && token->next != NULL)
			{
				if (check_red(token->type) == 1 && token->next != NULL)
				{
					file[j] = token->next->val_noquotes;
					redirection[j++] = token->val_noquotes;
				}
				else if (token->type == PIPE)
					break;
				token = token->next;
			}
			file_and_red = ft_addlist_files(file, redirection); 
			ft_lstaddback_files(&files, file_and_red);
			token = token->next;
		}
	}
	file[j] = 0;
	redirection[j] = 0;
	token = tmp;
}

int lenght_cmds (t_word	*token)
{
	int	size;
	t_word	*tmp;

	size = 0;
	tmp = token;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->next)
		{
			if (check_red(tmp->type) == 0 && check_red(tmp->next->type) == 0)
				size++;
		}
		else
			size++;
		tmp = tmp->next;
	}
	return (size);
}

// void ft_list_cmd (t_word	*token, t_cmd_node *cmd)
// {
// 	int	j;
// 	char **cmds;
// 	t_cmd_node* commands;
// 	t_word	*tmp;

// 	tmp = token;
// 	cmd = NULL;
// 	while (token != NULL)
// 	{
// 		cmds = (char **)malloc(sizeof(char *) * (lenght_cmds(token) + 1));
// 		if (cmds == NULL)
// 			return ;
// 		if (token->type == PIPE)
// 			token = token->next;
// 		// else if ((check_red(token->type) == 1 && (token->next == NULL || token->next->next == NULL)))
// 		// 	break;
// 		else
// 		{
// 			j = 0;
// 			while (token != NULL && token->type != PIPE)
// 			{
// 				puts("ok");
// 				if (token->type == PIPE || (check_red(token->type) == 1 && (token->next == NULL || token->next->next == NULL)))
// 					break;
// 				else if (check_red(token->type) == 1)
// 					{
//                 	token = token->next;
//                 	if (token != NULL) token = token->next;
//             		}
// 				else
// 				{
// 					cmds[j++] = token->val_noquotes;
// 					token = token->next;
// 				}
// 			}
// 			if ((check_red(token->type) == 1 && (token->next == NULL || token->next->next == NULL)))
// 				break;
// 			cmds[j] = 0;
// 			commands = ft_addlist_cmds(cmds); 
// 			ft_lstaddback_cmd(&cmd, commands);
// 			if (token)
// 				token = token->next;
// 		}
		
// 	}
// 	token = tmp;
// 	while (cmd)
// 	{
// 		j = 0;
// 		while (cmd->command[j])
// 		{
// 			printf("cmds : %s ", cmd->command[j]);
// 			j++;
// 		}
// 		puts("\n\n");
// 		cmd =cmd->next;
// 	}
// }

//   1 2 3 4 5 6 >> 7 << 8 | 9 10 | 11 12 | > 13 6

// while (token != NULL)
// 	{
// 		i = 0;
// 		j = 0;
// 		while (token->type != PIPE && token->next != NULL)
// 		{
// 			if (check_red(token->type) == 1 && token->next != NULL)
// 			{
// 				file[j] = token->next->val_noquotes;
// 				redirection[j] = token->val_noquotes;
// 				j++;
// 				i++;
// 			}
// 			token = token->next;
// 		}
// 		file_and_red = ft_addlist_files(file, redirection);
// 		ft_lstaddback_files(&files, file_and_red);
// 		token = token->next;
// 	}

// t_red_node *tmp = files;
// while(tmp != NULL)
// {
// 	i = 0;
// 	while (tmp->file[i] && tmp->red[i])
// 	{
// 		printf(" file : %s ", tmp->file[i]);
// 		printf(" red : %s  |", tmp->red[i]);
// 		i++;
// 	}
// 	printf("\n\n");
// 	tmp = tmp->next;
// }