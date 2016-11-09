NAME = fillit

HEAD = fillit.h

SRC = 	$(LIBFT)libft.a \
		utils.c \
		check.c \
		store.c \
		solve.c \
		main.c \

LIBFT = libft/

CCFLAGS = -Wall -Werror -Wextra

RM = rm -rf

all: $(NAME)

$(NAME):
	make -C $(LIBFT) re
	gcc $(CCFLAGS) -o $(NAME) $(SRC)

clean:
	$(RM) utils.o check.o store.o solve.o main.o
	make -C $(LIBFT) clean

fclean: clean
	make -C $(LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
