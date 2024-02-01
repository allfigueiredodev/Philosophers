NAME = philo
MAKE = make
CC = cc
FLAGS = -Wall -Werror -Wextra -g3
SRC = philosophers.c philosophers_utils.c philosophers_init.c lst_utils.c \
actions.c philosophers_init2.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) -I ./

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o) -I ./

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s -pthread ./philo 5 800 400 200 10

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re