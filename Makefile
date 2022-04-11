NAME	=	pipex

INCS	=	pipex.h

SRCS	=	./function/ft_split.c \
			./function/ft_strjoin.c \
			./function/ft_strncmp.c \
			./function/main.c \
			./function/parsing.c \
			./function/utils.c	\
			./function/ft_strlen.c

OBJS	=	${SRCS:%.c=%.o} \
			${INCS}

CC		=	clang

RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror #-g3 -fsanitize=thread

all: ${NAME}
			

${NAME}:	${OBJS}
			@$(CC) ${CFLAGS}  ${SRCS:.c=.o} -o $(NAME)

%.c%.o:
			@echo "compiling" $@
			@${CC} ${CFLAGS} -c $< -o $@

clean:
			${RM} ${SRCS:.c=.o}

fclean:		clean
			${RM} ${NAME}
re:			fclean all

.PHONY:		all clean fclean re