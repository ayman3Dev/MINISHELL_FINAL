NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

RM = rm -f

SRC = 	minishell.c check_line.c ft_add_list_token.c ft_add_token_outils.c ft_list_token.c \
		ft_strcmp.c ft_split.c\
		ft_check_syntax.c \
		list_function.c

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

