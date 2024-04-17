SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

SRC_PATH = ./src

SRC_NAME =	ft_malloc.c ft_free.c ft_realloc.c\
			show_alloc.c ft_show_alloc_hex.c\
			utils_print.c page_manip.c\

OBJS = ${SRCS:.c=.o}

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_${HOSTTYPE}.so

HEADER = -I "./includes" -I "./libft"

CC = clang

LIBFT = ./libft/libft.a

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -DMALLOC_OVERFLOW=1 

.c.o: 
			${CC} ${CFLAGS} ${HEADER} -c $< -o $@

${NAME}:	${OBJS} ${OBJSLIBFT}
			cd libft; $(MAKE);
			${CC} ${CFLAGS} ${HEADER} -o ${NAME} -shared -DMALLOC_OVERFLOW=1 ${OBJS} ${LIBFT}
			ln -s ${NAME} libft_malloc.so

all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJSLIBFT}

fclean:		clean
			cd libft; make fclean;
			${RM} libft_malloc*.so

re:			fclean all

.PHONY =	all clean fclean re
