NAME = get_next_line.a

CC= gcc

CCFLAGS= -Wall -Werror -Wextra

SRCS= get_next_line.c get_next_line_utils.c

OBJS= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
