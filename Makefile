SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

UNAME_S = $(shell uname -s)

SRC_PATH = ./src

SRC_NAME =	main.c

LIBFT_MALLOC = ./libft_malloc/libft_malloc_${HOSTTYPE}.so

OBJS = $(SRCS:.c=.o)

NAME = test

FLAGS = -Wall -Wextra -Werror

HEADER = -I "./libft_malloc/include"

CC = clang

RM = rm -f

CD = cd

.c.o:
		$(CC) ${FLAGS} ${HEADER} -c $< -o $@

${NAME}:	${OBJS}
			cd libft_malloc; $(MAKE);
			${CC} -o ${NAME} ${OBJS} ${FLAGS} ${LIBFT_MALLOC}

all: ${NAME}

clean:
		cd libft_malloc; make clean;
		${RM} ${OBJS}

fclean:		clean
			cd libft_malloc; make fclean;
			${RM} ${NAME}

re:	fclean all;

.PHONY =	all clean fclean re