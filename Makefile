NAME = philo

CMD = cc

CMD_D = gcc

CFLAGS   = -Wall -Wextra -Werror -Iincludes

CFLAGS_D = -Wall -Wextra -Werror -g -fsanitize=thread -pthread -Iincludes

CFLAGS_L = -Wall -Wextra -Werror -g -fsanitize=address -pthread -Iincludes

CFLAGS_V = -Wall -Wextra -Werror -g  -O1 -pthread -Iincludes

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
	$(CMD_D) $(CFLAGS_D) $(OBJS) -o $(NAME)

debug_valgrind : $(OBJS)
	$(CMD_D) $(CFLAGS_V) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
