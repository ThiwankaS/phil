NAME = philo

CMD = cc

CFLAGS   = -Wall -Wextra -Werror -Iincludes

CFLAGS_D = -Wall -Wextra -Werror -g -fsanitize=thread -pthread -lpthread -Iincludes

CFLAGS_L = -Wall -Wextra -Werror -g -fsanitize=address -pthread -lpthread -Iincludes

CFLAGS_V = -Wall -Wextra -Werror -g -pthread -lpthread -Iincludes

SRCS = \
	atol.c\
	checks.c\
	cycle.c\
	error.c\
	exit.c\
	helper.c\
	init.c\
	meals.c\
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
