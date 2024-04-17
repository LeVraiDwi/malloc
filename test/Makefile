SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

UNAME_S = $(shell uname -s)

SRC_PATH = ./src

SRC_NAME =	main.c

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LIBFT_MALLOC = ../libft_malloc_${HOSTTYPE}.so

OBJS = $(SRCS:.c=.o)

NAME = test

FLAGS = -Wall -Wextra -Werror 

HEADER = -I "../includes"

CC = clang

RM = rm -f

CD = cd

.c.o:
		$(CC) ${FLAGS} ${HEADER} -c $< -o $@

${NAME}:	${OBJS}
			cd ../; $(MAKE);
			${CC} -o ${NAME} ${OBJS} ${FLAGS} -lpthread ${LIBFT_MALLOC}

all: ${NAME}

clean:
		cd ../; make clean;
		${RM} ${OBJS}

fclean:		clean
			cd ../; make fclean;
			${RM} ${NAME}

re:	fclean all;

.PHONY =	all clean fclean re