# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/30 13:36:26 by mehakcan          #+#    #+#              #
#    Updated: 2024/07/30 16:29:27 by mehakcan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

RM = rm -rf

CF = -Wall -Wextra -Werror -g
SRC = src/main.c \
		src/exit.c \

LIBFT = libft/libft.a

OBJ_DIR = .objs

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) -lreadline

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C libft clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

iclean:
	@grep -v '^#' .gitignore | grep -v '^$$' | while read pattern; do \
		find . -name "$$pattern" -exec rm -rf {} +; \
	done

norm:
	@if norminette | grep -q "Error"; then \
		echo "Norminette: \033[31m[KO]\033[0m"; \
		norminette | grep "Error"; \
	else \
		echo "Norminette: \033[32m[OK]\033[0m"; \
	fi

.PHONY: all fclean clean re