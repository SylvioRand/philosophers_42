NAME = philo

SRC = main.c \
	  ./store_args.c \
	  ./utils/ft_putstr.c \
	  ./create_threads.c \
	  ./error_management/error_args.c \
	  ./error_management/err.c \
	  ./utils/ft_strlen.c \
	  ./utils/is_positive_numeric.c \

OBJS = ${SRC:.c=.o}

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror

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
