#include "minishell.h"

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

int	lenght_cmds(t_word	*token)
{
	int		size;
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

void	ft_list_cmd(t_word	*token, t_cmd_node *cmd)
{
	int			j;
	char		**cmds;
	t_cmd_node	*commands;
	t_word		*tmp;

	tmp = token;
	cmd = NULL;
	while (token != NULL)
	{
		cmds = (char **)malloc(sizeof(char *) * (lenght_cmds(token) + 1));
		if (cmds == NULL)
			return ;
		if (token->type == PIPE)
			token = token->next;
		else
		{
			j = 0;
			while (token != NULL && token->type != PIPE)
			{
				if (token->type == PIPE || (check_red(token->type) == 1
						&& (token->next == NULL || token->next->next == NULL)))
					break ;
				else if (check_red(token->type) == 1)
				{
					token = token->next;
					if (token != NULL)
						token = token->next;
				}
				else
				{
					cmds[j++] = token->val_noquotes;
					token = token->next;
				}
			}
			cmds[j] = 0;
			commands = ft_addlist_cmds(cmds); 
			ft_lstaddback_cmd(&cmd, commands);
			if (token != NULL && check_red(token->type) == 1
				&& (token->next == NULL || token->next->next == NULL))
				break ;
			if (token != NULL && token->type == PIPE)
				token = token->next;
		}
	}
	token = tmp;
}

// while (cmd)
// {
// 	j = 0;
// 	while (cmd->command[j])
// 	{
// 		printf("cmds : %s ", cmd->command[j]);
// 		j++;
// 	}
// 	puts("\n\n");
// 	cmd =cmd->next;
// }