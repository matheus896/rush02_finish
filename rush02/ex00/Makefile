NAME = rush-02
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c main_utils.c ft_utils.c ft_utils2.c solver.c solver_2.c dict_parser.c
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
