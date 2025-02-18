NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = 		src/pipex.c \
			src/child.c \
			src/functions/ft_split.c \
			src/functions/ft_strlen.c \
			src/functions/ft_strjoin.c

BONUSSRCS = 

OBJS = $(SRCS:.c=.o)
BONUSOBJS = $(BONUSSRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(OBJS) $(BONUSOBJS)
	ar rcs $(NAME) $(OBJS) $(BONUSOBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUSOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

rebonus: fclean bonus