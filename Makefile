NAME	=	pipex

INCS	=	pipex.h

SRCS	=	./function/ft_split.c \
			./function/ft_strjoin.c \
			./function/ft_strncmp.c \
			./function/main.c \
			./function/parsing.c 

OBJS	=	${SRCS:.c=.o}

CC		=	clang

RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror #-g3 -fsanitize=thread

all: ${NAME}
	@make -C ./ft_printf/ --no-print-directory
	

${NAME}:	${OBJS}
			mv ./ft_printf/libftprintf.a ./
			$(CC) ${CFLAGS} $(OBJS) -I $(INCS) -o $(NAME) libftprintf.a

.c.o:
			${CC} ${CFLAGS} -c $< -o $@ -I ${INCS}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
			rm libftprintf.a

re:			fclean all

.PHONY:		all clean fclean re