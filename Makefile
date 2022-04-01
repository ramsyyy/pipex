CC = gcc

NAME = pipex

PRINTFPATH = ./ft_printf/

PRINTFNAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror 


OBJ := $(.c=.o)

SRC = ./main.c

UTILS = ./function/* 

all : $(NAME)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME): $(OBJ)
		make -C $(PRINTFPATH)
		mv $(PRINTFPATH)$(PRINTFNAME) $(PRINTFNAME)
		${CC}  ${CFLAGS} $(UTILS) $(PRINTFNAME) -o ${NAME}

clean:
		rm -rf *.o && make -C $(PRINTFPATH) clean

fclean: clean
		rm -f $(PRINTFNAME) ${OBJS} $(NAME) && make -C $(PRINTFPATH) fclean

re: fclean all