NAME = philo

SRC = main.c \
	  ./store_args.c \
	  ./create_forks.c \
	  ./print_state.c \
	  ./monitor_death.c \
	  ./create_threads.c \
	  ./error_management/error_args.c \
	  ./error_management/err.c \
	  ./utils/ft_strlen.c \
	  ./utils/is_positive_numeric.c \
	  ./routine/eat.c \
	  ./routine/routine.c \
	  ./routine/sleep.c \
	  ./routine/think.c \
	  ./routine/eat_utils.c \

OBJS = ${SRC:.c=.o}

CC = gcc

RM = rm -rf

CFLAGS = -pthread  -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all : ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lpthread

clean:
	${RM} ${OBJS} 

fclean:
	${RM} ${OBJS} ${NAME}

re:
	${MAKE} fclean
	${MAKE} all

.PHONY: .c.o all clean fclean re
