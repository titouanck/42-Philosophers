SRCS =	${wildcard *.c}

OBJS = ${SRCS:.c=.o}
DEPS = ${SRCS:.c=.d}

INC = -I ./
LIBS = ${INC}

NAME = philo
CC = cc
# CFLAGS = -Wall -Wextra -Werror 
CFLAGS = -pthread

.c.o:
		${CC} ${CFLAGS} ${INC} -MMD -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} 
		cc -o ${NAME} ${CFLAGS} ${OBJS} ${LIBS}

all:	${NAME}

clean:	
	@	rm -f ${OBJS} ${DEPS}

fclean:	clean;
	@	rm -f ${NAME}

re:	fclean all

-include ${DEPS}
