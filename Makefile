NAME = philo

CMD = cc

CFLAGS = -Wall -Wextra -Werror

CFLAGS_D = -Wall -Wextra -Werror -g -fsanitize=thread -pthread -lpthread

CFLAGS_L = -Wall -Wextra -Werror -g -fsanitize=address -pthread -lpthread

CFLAGS_V = -Wall -Wextra -Werror -g -pthread -lpthread

SRCS = \
	atol.c\
	checks.c\
	cycle.c\
	error.c\
	exit.c\
	init.c\
	utils.c\
	validate.c\
	main.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CMD) $(CFLAGS) $(OBJS) -o $(NAME)

debug_leaks : $(OBJS)
	$(CMD) $(CFLAGS_L) $(OBJS) -o $(NAME)

debug_drc : $(OBJS)
	$(CMD) $(CFLAGS_D) $(OBJS) -o $(NAME)

debug_valgrind : $(OBJS)
	$(CMD) $(CFLAGS_V) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
