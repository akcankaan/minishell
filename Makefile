CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCDIR = src
INCDIR = includes
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/prompt.c \
       $(SRCDIR)/lexer.c \
       $(SRCDIR)/exit.c \
       $(SRCDIR)/command.c

OBJS = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re
