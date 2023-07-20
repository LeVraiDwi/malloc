SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

SRCSBONUS = $(addprefix $(SRC_PATH)/,$(SRC_BONUS))

SRC_PATH = ./src

SRC_NAME =	ft_malloc.c ft_free.c ft_realloc.c\
			show_alloc.c ft_show_alloc_hex.c\

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${SRCSBONUS:.c=.o}

NAME = libft_malloc_${HOSTTYPE}.so

HEADER = -I "./include" -I "./libft"

CC = clang

LIBFT = ./libft/libft.a

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -DMALLOC_OVERFLOW=1 

.c.o: 
			${CC} ${CFLAGS} ${HEADER} -c $< -o $@

${NAME}:	${OBJS}
			cd libft; $(MAKE);
			${CC} ${CFLAGS} ${HEADER} -o ${NAME} -shared -DMALLOC_OVERFLOW=1 ${OBJS} ${LIBFT}

all:		${NAME}

clean:
			cd libft; make clean;
			${RM} ${OBJS} ${OBJSBONUS}

fclean:		clean
			cd libft; make fclean;
			${RM} ${NAME}

re:			fclean all

.PHONY =	all clean fclean re
