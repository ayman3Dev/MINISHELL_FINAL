#ifndef MINISHELL
#define MINISHELL

#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <readline/history.h>

//  #define PIPE 0
 #define IN_RED  1

typedef enum e_type {
	WORD = 0,
	PIPE = 1,
	L_RED = 2,
	R_RED = 4,
	DL_RED = 5,
	DR_RED = 6,
}	t_type;

typedef struct s_red_node
{
	char			**red;
	char			**file;
	t_type			type;
	struct s_red_node	*next;
}	t_red_node;

typedef struct s_com_node
{
	char 			**command;
	struct s_com_node	*next;
}	t_com_node;

typedef struct s_node
{
	int data;
	char **redirection;
	char **command;
	char **com;
	t_red_node *red;
	t_com_node *cmd;
	struct s_node	*next;
}	t_node;


typedef struct s_word
{
	t_type			type;
	char			*value;
	int				here_doc_fd;
	struct s_word	*next;
	struct s_word	*prev;
}	t_word;

int	ft_check_line(char *line);

//token_list
t_word		*ft_list_tokn(char *all_command, t_word *token);
t_word		*ft_addlist_token(char *word);
void		ft_lstaddback_token(t_word **list, t_word*new_node);
//token_list


//libft
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);
//libft

//chech_syntax
int			check_syntax(t_word *token);
int			ft_check_quotes(char c, int *sign);
int			check_space(char c, int sign);
int			ft_is_space(char c);
char		*check_char(char c);
//list_function
void	ft_lstclear_token(t_word **list);

#endif