# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chansen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/08 21:07:00 by chansen           #+#    #+#              #
#    Updated: 2016/11/08 21:07:02 by chansen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

HEAD = fillit.h

SRC = 	xlibft.c \
		libft.c \
		utils.c \
		check.c \
		store.c \
		solve.c \
		main.c \

CCFLAGS = -Wall -Werror -Wextra

RM = rm -rf

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CCFLAGS) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

re: fclean all

fclean: clean
	$(RM) $(NAME)

.PHONY: all clean
