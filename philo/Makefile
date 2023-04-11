RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
ORANGE='\033[0;33m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
LIGHTGRAY='\033[0;37m'
DARKGRAY='\033[1;30m'
LIGHTRED='\033[1;31m'
LIGHTGREEN='\033[1;32m'
LIGHTBLUE='\033[1;34m'
LIGHTPURPLE='\033[1;35m'
LIGHTCYAN='\033[1;36m'
YELLOW='\033[1;33m'
WHITE='\033[1;37m'
NC='\033[0m'

SRCS_PATH += ./
SRCS += actions.c
SRCS += atoi_spe.c
SRCS += check_death.c
SRCS += ft_putstr_fd.c
SRCS += main.c
SRCS += philos.c
SRCS += print_state.c
SRCS += properties.c
SRCS += routine.c
SRCS += threads.c
SRCS += time.c

TERM_WIDTH := $(shell tput cols)
SHELL = /bin/bash

FT_PRINTF_PATH = 42-ft_printf

vpath %.c ${SRCS_PATH}

INC = -I ./

OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}
OBJS_PATH = ./objs/

CC = cc
CFLAGS = -Wall -Wextra -Werror -lpthread
NAME = philo

all: ${NAME}

${OBJS}: ${OBJS_PATH}/%.o: %.c Makefile
	@	mkdir -p ${OBJS_PATH}
	@	$(COLORCOMPIL)
	@	${CC} ${CFLAGS} -c $< -o $@ ${INC}

${NAME}:  ${OBJS}
	@	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS} ${INC}	
	@	echo -ne "\r\033[2K" $(LIGHTGREEN) "→ $(NAME) OK!\n"$(NC)

clean:	
	@	echo -ne "\r\033[2K" $(LIGHTGREEN) "→ $(NAME) cleaned\n"$(NC)
	@	rm -rf ${OBJS_PATH}


fclean:	clean;
	@	rm -f ${NAME} 


re:	fclean ${NAME}

# Crédit : https://github.com/romann-broque (42: rbroque)
ifndef COLORCOMPIL
ifeq ($(shell test $(TERM_WIDTH) -gt 69; echo $$?), 0)
COLORCOMPIL = \
	if [ "$(shell test $P -lt 33; echo $$?)" = "0" ]; then \
    	echo -ne "\r\033[2K" $(LIGHTRED) "[$(P)%] "$(DARKGRAY) "Compiling MiniShell" $(WHITE) "$<"; \
	else \
		if [ "$(shell test $P -lt 66; echo $$?)" = "0" ]; then \
    		echo -ne "\r\033[2K" $(YELLOW) "[$(P)%]" $(DARKGRAY) "Compiling MiniShell" $(WHITE) "$<"; \
		else \
       		echo -ne "\r\033[2K" $(LIGHTGREEN) "[$(P)%]" $(DARKGRAY) "Compiling MiniShell" $(WHITE) "$<"; \
		fi \
	fi
else
COLORCOMPIL = \
	if [ "$(shell test $P -lt 33; echo $$?)" = "0" ]; then \
    	echo -ne "\r\033[2K" $(LIGHTRED) "[$(P)%] "$(DARKGRAY) "Compiling MiniShell"; \
	else \
		if [ "$(shell test $P -lt 66; echo $$?)" = "0" ]; then \
    		echo -ne "\r\033[2K" $(YELLOW) "[$(P)%]" $(DARKGRAY) "Compiling MiniShell"; \
		else \
       		echo -ne "\r\033[2K" $(LIGHTGREEN) "[$(P)%]" $(DARKGRAY) "Compiling MiniShell"; \
		fi \
	fi
endif
T := $(words $(SRCS))
N := x
C = $(words $N)$(eval N := x $N)
P = `expr $C '*' 100 / $T / 5`
endif
# Crédit : https://github.com/romann-broque (42: rbroque)

.PHONY: all clean fclean re 