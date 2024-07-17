.PHONY: all clean fclean re

CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = minishell

CFILES = main.c\
         parser/main_utils.c\
         parser/tokenizer.c\
         parser/get_tokens.c\
         parser/checker.c\
		 parser/signals.c\
         parser/reform_cmds.c\
         parser/expansion.c\
         parser/expansion_utils.c\
         parser/tokenizer_utils.c\
         parser/parser.c\
         parser/linked_cmds.c\
         parser/linked_redirection.c\
         parser/parser_utils.c\
		 Execution/exe_utils.c\
		 Execution/execution_errors.c\
		 Execution/execution.c\
		 Execution/manage_redirection.c\
		 Execution/manage_files.c\
		 Execution/redirection.c\
		 Execution/heredoc.c\
		 Execution/execution_helpers.c\
		 Execution/execution_helpers1.c\
		 Execution/execution_helpers2.c\
		 Execution/execution_helpers3.c\
		 Execution/execution_helpers4.c\
		 Builtins/Builtinutils.c\
		 Builtins/ft_cd.c\
		 Builtins/ft_echo.c\
		 Builtins/ft_env.c\
		 Builtins/ft_exit.c\
		 Builtins/ft_export.c\
		 Builtins/ft_pwd.c\
		 Builtins/ft_unset.c\
		 Builtins/env_utils.c\
		 Builtins/export_utils.c\

OBJ = $(CFILES:.c=.o)
READLINEDIR  =  $(shell brew --prefix readline)
all: lib $(NAME)

lib:
	@make -C libft

$(OBJ) : %.o: %.c includes/minishell.h
	@$(CC) $(FLAGS) -c $< -o $@ -I$(READLINEDIR)/include

$(NAME): libft/libft.a $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -lreadline -Llibft -lft -o $(NAME) -L$(READLINEDIR)/lib -lreadline
	@echo Making ... Done.

clean:
	$(RM) $(OBJ)
	make -C libft clean
	@echo Cleaning ... Done.

fclean: clean
	$(RM) $(NAME)
	@make -C libft fclean

re: fclean all