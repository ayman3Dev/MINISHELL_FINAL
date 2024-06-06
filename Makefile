NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

SRC = 	minishell.c check_line.c ft_add_list_token.c ft_list_token.c \
		ft_strcmp.c ft_split.c ft_substr.c ft_strdup.c \
		ft_check_syntax.c make_space.c \
		list_function.c \
		ft_list_files.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline 

%.o: %.c minishell.h
		 $(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJ) 

fclean: clean
		$(RM) $(NAME)

re: fclean all

