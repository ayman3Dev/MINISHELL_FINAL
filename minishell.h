#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <readline/history.h>

typedef enum e_type
{
	WORD = 0,
	PIPE = 1,
	L_RED = 2,
	R_RED = 4,
	DL_RED = 5,
	DR_RED = 6,
}	t_type;

typedef struct s_red_node
{
	char				**red;
	char				**file;
	t_type				type;
	struct s_red_node	*next;
}	t_red_node;

typedef struct s_cmd_node
{
	char				**command;
	struct s_cmd_node	*next;
}	t_cmd_node;

// typedef struct s_node
// {
// 	int				data;
// 	char			**redirection;
// 	char			**command;
// 	char			**com;
// 	t_red_node		*red;
// 	t_cmd_node		*cmd;
// 	struct s_node	*next;
// }	t_node;

typedef struct s_word
{
	t_type			type;
	char			*value;
	char			*val_noquotes;
	int				quotes_type;
	int				here_doc_fd;
	struct s_word	*next;
	struct s_word	*prev;
}	t_word;

//expand
typedef struct s_env
{
	char			*variable;
	char			*value;
	char			*fil;
	long			status;
	struct s_env	*next;
}	t_env;
//expand

//token_list
t_word		*ft_list_tokn(char *all_command, t_word *token, t_env *envirment);
t_word		*ft_addlist_token(char *word);
void		ft_lstaddback_token(t_word **list, t_word*new_node);
int			remove_quotes(t_word *token);
//token_list

//libft
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_itoa(int n);
long		ft_atoi(const char *str, t_env *env);
//libft

//chech_syntax
int			check_syntax(t_word *token);
int			ft_check_quotes(char c, int *sign);
int			check_space(char c, int sign);
int			ft_is_space(char c);
char		*check_char(char c);
int			check_quotes(char *line);
int			check_red(int type);

//list_function
void		ft_lstclear_token(t_word **list);

//list_files
void		ft_list_file(t_word	*token, t_red_node *files);

//listcommands
void		ft_list_cmd(t_word *token, t_cmd_node *cmd);

//print error
void		print_error(char *token);

//expand
void		ft_env(char **ev, t_env **env);
int			size_stack(t_env *a);
void		ft_lstadd_back(t_env **lst, t_env *new);
t_env		*ft_lstlast(t_env *lst);
t_env		*ft_lstnew(char *var, char *value);
t_env		*point_node(t_env *env, char *name);
char		*get_variabl(char *line);
int			check_char_expand (char c);
#endif