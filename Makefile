# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 12:49:32 by iecer             #+#    #+#              #
#    Updated: 2024/09/10 12:56:20 by mehakcan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC		= cc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror

SRC =	src/main.c					\
		garbage_collecter/alloc.c	\
		garbage_collecter/clean.c	\
		src/check/cmd_check.c		\
		src/command/cmd_cd.c		\
		src/command/cmd_env.c		\
		src/command/cmd_pwd.c		\
		src/command/cmd_exit.c		\
		src/command/cmd_echo.c		\
		src/command/cmd_unset.c		\
		src/command/cmd_export.c	\
		src/excec/parser.c			\
		src/excec/use_execve.c		\
		src/excec/execute_conf.c	\
		src/lexer/lexer.c			\
		src/lexer/token.c			\
		src/signal/signal.c			\
		src/expander/expander.c		\
		src/utils/exit.c			\
		src/utils/utils.c			\
		src/utils/rdir_utils.c		\
		src/utils/parser_utils.c	\
		src/utils/builtin_utils.c	\

LIBFT = libft/libft.a

OBJ_DIR = .objs

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) -lreadline

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C libft clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all fclean clean re
