NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = 		src/pipex.c \
			src/child.c \
			src/functions/ft_split.c \
			src/functions/ft_strlen.c \
			src/functions/ft_strjoin.c \
			src/functions/ft_strncmp.c \
			src/functions/ft_strdup.c \
			src/functions/ft_print_string.c \
			src/functions/ft_print_error.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUSOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all