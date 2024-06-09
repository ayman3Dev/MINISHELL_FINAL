#include "minishell.h"
void	remove_variab(t_env **env, char *name)
{
	t_env	*node;
	t_env	*tmp;

	tmp = *env;
	node = point_node(*env, name);
	if (node == NULL)
		return ;
	while (*env)
	{
		if (ft_strncmp((*env)->next->variable, name, ft_strlen(name) + 1) == 0)
		{
			(*env)->next = (*env)->next->next;
			free(node->variable);
			free(node->value);
			free(node);
			*env = tmp;
			return ;
		}
		*env = (*env)->next;
	}
	*env = tmp;
}
//******************************


void	init(char *line, int *i, int *t)
{
	while (line[*i])
	{
		if (line[*i] == '=')
		{
			*t = 1;
			break ;
		}
		(*i)++;
	}
}

char	*get_value(char *line)
{
	int		i;
	int		j;
	int		t;
	char	*value;

	i = 0;
	j = 0;
	t = 0;
	if (!line)
		return (NULL);
	init(line, &i, &t);
	if (t == 0)
		return (NULL);
	t = i + 1;
	while (line[++i] != '\0')
		j++;
	value = (char *)malloc(j + 1);
	if (!value)
		return (NULL);
	i = 0;
	while (line[t])
		value[i++] = line[t++];
	value[i] = '\0';
	return (value);
}

void	modif_env(t_env **env)
{
	t_env	*new;

	if (point_node(*env, "PATH") == NULL)
	{
		new = ft_lstnew(ft_strdup("PATH"), ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
		ft_lstadd_back(env, new);
	}
	remove_variab(env, "PWD");
	remove_variab(env, "OLDPWD");
	new = ft_lstnew(ft_strdup("PWD"), getcwd(NULL, 0));
	ft_lstadd_back(env, new);
	new = ft_lstnew(ft_strdup("OLDPWD"), NULL);
	ft_lstadd_back(env, new);
}

void	modif_shlvl(t_env **env, t_env *new, char *var, char *val)
{
	t_env	*node;
	long	val_shlvl;

	val_shlvl = 1;
	node = point_node(*env, "SHLVL");
	if (!node)
	{
		var = ft_strdup("SHLVL");
		val = ft_strdup("1");
		new = ft_lstnew(var, val);
		ft_lstadd_back(env, new);
	}
	else if (!node->value || (node->value[0] == '\0'))
		node->value = ft_strdup("1");
	else if (node->value[0] == '-')
		node->value = ft_strdup("0");
	else
	{
		val_shlvl += ft_atoi(node->value, *env);
		node->value = ft_itoa(val_shlvl);
	}
}
t_env	*point_node(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strncmp(env->variable, name, ft_strlen(name) + 1) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*ft_lstnew(char *var, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->variable = var;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		(*lst) = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}

int	size_stack(t_env *a)
{
	int		size;

	if (!a)
		return (-1);
	size = 0;
	while (a)
	{
		size++;
		a = a -> next;
	}
	return (size);
}

char	*get_variabl(char *line)
{
	int		i;
	char	*variable;

	i = 0;
	if (!line)
		return (NULL);
	while (check_char_expand (line[i]) == 1)
		i++;
	if (i == 0)
		return (NULL);
	variable = (char *)malloc(i + 1);
	if (!variable)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '=' || line[i] == '"' || line[i] == '$' || line[i] == ' ' || line[i] == '\0')
			break ;
		variable[i] = line[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

void	ft_env(char **ev, t_env **env)
{
	char	*var;
	char	*val;
	t_env	*new;
	int		i;

	var = NULL;
	val = NULL;
	i = 0;
	while (ev[i])
	{
		var = get_variabl(ev[i]);
		val = get_value(ev[i]);
		new = ft_lstnew(var, val);
		ft_lstadd_back(env, new);
		i++;
	}
	modif_env(env);
	modif_shlvl(env, new, var, val);
}

// int	main(int argc, char *argv[], char **ev)
// {
// 	t_env	*env;
// 	char	**cmd;

// 	(void)argc;
// 	(void)argv;
// 	cmd = NULL;
// 	ft_env(ev, &env);
// 	display_env(env);
// 	return (0);
// }