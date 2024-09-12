NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRCS =  utils.c ft_atoi.c philo_init.c philo.c main.c actions.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re