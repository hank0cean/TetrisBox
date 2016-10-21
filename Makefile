# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chansen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/20 17:17:45 by chansen           #+#    #+#              #
#    Updated: 2016/10/20 17:31:36 by chansen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

HEAD = fillit.h

SRC = main.c \
	  open.c \

OBJ = $(SRC:.c=.o)

LIBFT = ../libft/

CC = gcc

FLAGS = -Wall -Wextra -Werror

RM = rm -f

all:
	$(CC) $(FLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFT)

fclean:
	clean $(RM) $(NAME)
	make fclean -C $(LIBFT)

re:
	clean all
